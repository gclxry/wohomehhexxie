
#include "stdafx.h"
#include "TestDx9.h"


#define RELEASE_COM_OBJECT(obj)					{if((obj) != NULL) {(obj)->Release(); (obj) = NULL;}}
// �����ʽ
#define CUSTOMFVF								(D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX1)

// �Զ��嶥���ʽ
struct MY_VERTEX_TYPE
{
	FLOAT X, Y, Z;
	D3DVECTOR NORMAL;
	FLOAT U, V;
};

CDxD3DRender::CDxD3DRender()
{
	m_pD3d9 = NULL;
	m_pD3d9Device = NULL;
	m_pVertexBuffer = NULL;
	m_pTexture = NULL;
	m_pD3dTargetSurface = NULL;
	m_pSysSurface = NULL;

	m_RenderRect.SetRectEmpty();
}

CDxD3DRender::~CDxD3DRender()
{

}

void CDxD3DRender::CreateTextureFromHBITMAP(HBITMAP hBmp)
{
	if (hBmp == NULL || m_RgnBmpDc.GetBits() == NULL)
		return;

	GetBitmapBits(hBmp, 4 * m_RenderRect.Width() * m_RenderRect.Height(), m_RgnBmpDc.GetBits());

	HRESULT hRet = m_pD3d9Device->CreateTexture(m_RenderRect.Width(), m_RenderRect.Height(),
		1, D3DUSAGE_DYNAMIC, D3DFMT_A8R8G8B8, D3DPOOL_DEFAULT, &m_pTexture, NULL);

	if (m_pTexture != NULL)
	{
		D3DLOCKED_RECT LockedRect;
		RECT rcSurface = {0, 0, m_RenderRect.Width(), m_RenderRect.Height()};

		hRet = m_pTexture->LockRect(0, &LockedRect, &rcSurface, D3DLOCK_READONLY);
		memcpy(LockedRect.pBits, m_RgnBmpDc.GetBits(), 4 * m_RenderRect.Width() * m_RenderRect.Height());
		hRet = m_pTexture->UnlockRect(0);
	}
}

void CDxD3DRender::InitDrawGraphics()
{
/*	// --------- ���ļ���������
	HRESULT hRet = D3DXCreateTextureFromFileEx(
		m_pD3d9Device, 
		_T("D:\\TestSkin\\textwrap.bmp"), 
		m_RenderRect.Width(), m_RenderRect.Height(),
		D3DX_DEFAULT, D3DUSAGE_RENDERTARGET, 
		D3DFMT_X8R8G8B8, D3DPOOL_DEFAULT,    
		D3DX_DEFAULT, D3DX_DEFAULT, 0, NULL, NULL,
		&m_pTexture);*/

	// ��Ⱦ��������
	MY_VERTEX_TYPE DemoVertices[] =
	{
		{ -5.0f, 5.0f, -5.0f, 0, 0, -1, 0, 0 },
		{ 5.0f, 5.0f, -5.0f, 0, 0, -1, 1, 0 },
		{ -5.0f, -5.0f, -5.0f, 0, 0, -1, 0, 1 },
		{ 5.0f, -5.0f, -5.0f, 0, 0, -1, 1, 1 },
	};

	// ����һ��������24���������ݵ�buffer
	m_pD3d9Device->CreateVertexBuffer(24 * sizeof(MY_VERTEX_TYPE), 0,
		CUSTOMFVF, D3DPOOL_MANAGED, &m_pVertexBuffer, NULL);

	// ���ö�������
	VOID* pVoid = NULL;    
	m_pVertexBuffer->Lock(0, 0, (void**)&pVoid, 0);
	memcpy(pVoid, DemoVertices, sizeof(DemoVertices));
	m_pVertexBuffer->Unlock();
}

void CDxD3DRender::InitD3d9Device(HWND hWnd, HBITMAP hBmp)
{
	if (!::IsWindow(hWnd))
		return;

	m_RenderRect.SetRectEmpty();
	::GetClientRect(hWnd, m_RenderRect);

	m_RgnBmpDc.Create(m_RenderRect.Width(), m_RenderRect.Height());

	if (m_RgnBmpDc.GetSafeHdc() == NULL)
		return;


//////////////////////////////////////////////////////////////////////////
	// ��ʼ��D3d�豸
	m_pD3d9 = Direct3DCreate9(D3D_SDK_VERSION);

	D3DPRESENT_PARAMETERS D3dPp;
	ZeroMemory(&D3dPp, sizeof(D3dPp));
	D3dPp.Windowed = TRUE;
	D3dPp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	D3dPp.hDeviceWindow = hWnd;
	D3dPp.BackBufferFormat = D3DFMT_X8R8G8B8;
	D3dPp.BackBufferWidth = m_RenderRect.Width();
	D3dPp.BackBufferHeight = m_RenderRect.Height();

	HRESULT hRet = m_pD3d9->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL,
		hWnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &D3dPp, &m_pD3d9Device);

	if (FAILED(m_pD3d9Device->CreateRenderTarget(m_RenderRect.Width(), m_RenderRect.Height(), 
		D3DFMT_A8R8G8B8, D3DMULTISAMPLE_NONE, 0, false, &m_pD3dTargetSurface, NULL)))
	{
		return;
	}
	m_pD3d9Device->SetRenderTarget(0, m_pD3dTargetSurface);

	m_pD3d9Device->CreateOffscreenPlainSurface(m_RenderRect.Width(), m_RenderRect.Height(), 
		D3DFMT_A8R8G8B8, D3DPOOL_SYSTEMMEM, &m_pSysSurface, NULL);






	// ��ʼ����ͼ����
	CreateTextureFromHBITMAP(hBmp);
	InitDrawGraphics();

//////////////////////////////////////////////////////////////////////////
	// ������Ⱦ״̬

	// �رչ���Ч��
	m_pD3d9Device->SetRenderState(D3DRS_LIGHTING, FALSE);
	// ������Ȳ���
	m_pD3d9Device->SetRenderState(D3DRS_ZENABLE, TRUE);
	// ���޳��κ��棨D3DCULL_NONE��ͼƬ����Ҳ��Ⱦ��
	m_pD3d9Device->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

//////////////////////////////////////////////////////////////////////////
	// �����Ӿ�������������� D3DTS_VIEW��

	// �Ӿ��ı����
	D3DXMATRIX MatView;
	// ������㣨����λ�ã�
	D3DXVECTOR3 CameraVct(0.0f, 0.0f, -19.5f);
	// �۲�㣬Ŀ��λ������
	D3DXVECTOR3 LookatVct(0.0f, 0.0f, 0.0f);
	// ��ǰ��������ϵ���Ϸ�������
	D3DXVECTOR3 UpVct(0.0f, 1.0f, 0.0f);
	// ���ù۲����
	D3DXMatrixLookAtLH(&MatView, &CameraVct, &LookatVct, &UpVct);
	// ���ñ任����
	m_pD3d9Device->SetTransform(D3DTS_VIEW, &MatView);

//////////////////////////////////////////////////////////////////////////
	// ����Z��ͶӰ����͸�Ӿ��� D3DTS_PROJECTION��

	// Z��ͶӰ��������
	D3DXMATRIX MatZProjection;  

	// ����һ����������ϵ��͸��ͶӰ����
	// ����һ��ָ��D3DXMATRIX �ṹ�Ĳ����������
	// ���������۲�ʱy�᷽��ĽǶȣ����ȣ������ǹ۲췶Χ�нǡ�
	// ���������ݺ�ȣ����ӿռ��ȳ��Ը߶ȡ�
	// �����ģ����ü���λ��Zֵ��
	// �����壺Զ�ü���λ��Zֵ��
	D3DXMatrixPerspectiveFovLH(&MatZProjection, D3DXToRadian(45.0f),  
		(FLOAT)m_RenderRect.Width() / (FLOAT)m_RenderRect.Height(), 0.0f, 100.0f);   

	m_pD3d9Device->SetTransform(D3DTS_PROJECTION, &MatZProjection);

	// ���ù̶���Ⱦ�ܵ��Ķ����ʽ
	m_pD3d9Device->SetFVF(CUSTOMFVF);
}

HDC CDxD3DRender::GetD3dRenderTargetData()
{
	D3DLOCKED_RECT LockedRect;
	RECT rcSurface = {0, 0, m_RenderRect.Width(), m_RenderRect.Height()};

	m_pD3d9Device->GetRenderTargetData(m_pD3dTargetSurface, m_pSysSurface);
	m_pSysSurface->LockRect(&LockedRect, &rcSurface, D3DLOCK_READONLY);
	memcpy(m_RgnBmpDc.GetBits(), LockedRect.pBits, 4 * m_RenderRect.Width() * m_RenderRect.Height());
	m_pSysSurface->UnlockRect();

	return m_RgnBmpDc.GetSafeHdc();
}

void CDxD3DRender::D3dRender()
{
	if (m_pD3d9Device == NULL)
		return;

	m_pD3d9Device->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_ARGB(0, 0, 0, 0), 1.0f, 0);
	m_pD3d9Device->Clear(0, NULL, D3DCLEAR_ZBUFFER, D3DCOLOR_ARGB(0, 0, 0, 0), 1.0f, 0);

	m_pD3d9Device->BeginScene();

	static float sfSpeed = (float)0.02;
	sfSpeed *= (float)1.0025;

	if (sfSpeed > (float)0.10)
		sfSpeed = (float)0.10;

	static float sfIndex = (float)0.0;
	sfIndex += sfSpeed;

	D3DXMATRIX MatRotateX;

	// ��ָ������Y��Ƕȣ���X��ǶȺ�Z��Ƕȴ�����ת����
	// ����һ��ָ��D3DXMATRIX�ṹ�Ĳ����������
	// ������������Y����ת�Ƕȣ���λ���ȣ�
	// ������������X����ת�Ƕȣ���λ���ȣ�
	// �����ģ�����Z����ת�Ƕȣ���λ���ȣ�
	// �������ı任˳����������Z����ת������������X����ת�����������Y����ת����Щ�������������ı�������ϵ��˵��
	D3DXMatrixRotationYawPitchRoll(&MatRotateX, sfIndex, sfIndex / (float)4.0, sfIndex / (float)4.0);

	// ������������
	m_pD3d9Device->SetTransform(D3DTS_WORLDMATRIX(0), &MatRotateX);
	// �󶨶��㻺�嵽�豸������
	m_pD3d9Device->SetStreamSource(0, m_pVertexBuffer, 0, sizeof(MY_VERTEX_TYPE));

	// ���ù���������������һ��Direct3D��������������ͼƬ��ƽ����������������������������
	m_pD3d9Device->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR); 
	m_pD3d9Device->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);   

	// ��������
	m_pD3d9Device->SetTexture(0, m_pTexture);

	// ����3D��Ⱦģʽ
	// �ӵ�0���㿪ʼ�� D3DPT_TRIANGLESTRIP ģʽ��Ⱦ2��������
	m_pD3d9Device->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

	m_pD3d9Device->EndScene();
	// ����ǰ�󻺳�
	m_pD3d9Device->Present(NULL, NULL, NULL, NULL);
}

void CDxD3DRender::CleanupD3d9()
{
	RELEASE_COM_OBJECT(m_pVertexBuffer);
	RELEASE_COM_OBJECT(m_pTexture);
	RELEASE_COM_OBJECT(m_pSysSurface);
	RELEASE_COM_OBJECT(m_pD3dTargetSurface);
	RELEASE_COM_OBJECT(m_pD3d9Device);
	RELEASE_COM_OBJECT(m_pD3d9);
	m_RgnBmpDc.Delete();
}
