
#include "stdafx.h"
#include "TestDx9.h"

LPDIRECT3D9 g_pD3d9 = NULL;
LPDIRECT3DDEVICE9 g_pD3d9Device = NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVertexBuffer = NULL;
LPDIRECT3DTEXTURE9 g_pTexture = NULL;
IDirect3DSurface9 *g_pD3d9Surface = NULL; 

#define RELEASE_COM_OBJECT(obj)					{if((obj) != NULL) {(obj)->Release(); (obj) = NULL;}}
// �����ʽ
#define CUSTOMFVF								(D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX1)

struct MY_VERTEX_TYPE
{
	FLOAT X, Y, Z;
	D3DVECTOR NORMAL;
	FLOAT U, V;
};

void InitDrawGraphics()
{
	// --------- ���ļ���������
	HRESULT hRet = D3DXCreateTextureFromFileEx(
		g_pD3d9Device, 
		_T("D:\\TestSkin\\textwrap.bmp"), 
		512,
		512, 
		D3DX_DEFAULT, D3DUSAGE_RENDERTARGET, 
		D3DFMT_X8R8G8B8, D3DPOOL_DEFAULT,    
		D3DX_DEFAULT, D3DX_DEFAULT, 0, NULL, NULL,
		&g_pTexture);

	// ��Ⱦ��������
	MY_VERTEX_TYPE DemoVertices[] =
	{
		{ -5.0f, 5.0f, -5.0f, 0, 0, -1, 0, 0 },
		{ 5.0f, 5.0f, -5.0f, 0, 0, -1, 1, 0 },
		{ -5.0f, -5.0f, -5.0f, 0, 0, -1, 0, 1 },
		{ 5.0f, -5.0f, -5.0f, 0, 0, -1, 1, 1 },
	};

	// ����һ��������24���������ݵ�buffer
	hRet = g_pD3d9Device->CreateVertexBuffer(24 * sizeof(MY_VERTEX_TYPE), 0,
		CUSTOMFVF, D3DPOOL_MANAGED, &g_pVertexBuffer, NULL);

	// ���ö�������
	VOID* pVoid = NULL;    
	g_pVertexBuffer->Lock(0, 0, (void**)&pVoid, 0);
	memcpy(pVoid, DemoVertices, sizeof(DemoVertices));
	g_pVertexBuffer->Unlock();
}

void InitD3d9Device(HWND hWnd)
{
	CRect ClientRect;
	::GetClientRect(hWnd, ClientRect);

//////////////////////////////////////////////////////////////////////////
	// ��ʼ��D3d�豸
	g_pD3d9 = Direct3DCreate9(D3D_SDK_VERSION);

	D3DPRESENT_PARAMETERS D3dPp;
	ZeroMemory(&D3dPp, sizeof(D3dPp));
	D3dPp.Windowed = TRUE;
	D3dPp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	D3dPp.hDeviceWindow = hWnd;
	D3dPp.BackBufferFormat = D3DFMT_X8R8G8B8;
	D3dPp.BackBufferWidth = ClientRect.Width();
	D3dPp.BackBufferHeight = ClientRect.Height();

	HRESULT hRet = g_pD3d9->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL,
		hWnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &D3dPp, &g_pD3d9Device);

	// ��ʼ����ͼ����
	InitDrawGraphics();

//////////////////////////////////////////////////////////////////////////
	// ������Ⱦ״̬

	// �رչ���Ч��
	g_pD3d9Device->SetRenderState(D3DRS_LIGHTING, FALSE);
	// ������Ȳ���
	g_pD3d9Device->SetRenderState(D3DRS_ZENABLE, TRUE);
	// ���޳��κ��棨D3DCULL_NONE��ͼƬ����Ҳ��Ⱦ��
	g_pD3d9Device->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

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
	g_pD3d9Device->SetTransform(D3DTS_VIEW, &MatView);

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
		(FLOAT)ClientRect.Width() / (FLOAT)ClientRect.Height(), 0.0f, 100.0f);   

	g_pD3d9Device->SetTransform(D3DTS_PROJECTION, &MatZProjection);

	// ���ù̶���Ⱦ�ܵ��Ķ����ʽ
	g_pD3d9Device->SetFVF(CUSTOMFVF);

	// ȡ��������Ⱦ���������
	g_pD3d9Device->CreateOffscreenPlainSurface(512, 512, D3DFMT_A8R8G8B8, D3DPOOL_DEFAULT, &g_pD3d9Surface, NULL);

	// --------- ���ļ������������
	hRet = D3DXLoadSurfaceFromFile(g_pD3d9Surface, NULL, NULL, _T("D:\\TestSkin\\textwrap.bmp"), NULL, D3DX_DEFAULT, 0, NULL);
}

void Render()
{
	if (g_pD3d9Device == NULL)
		return;

	g_pD3d9Device->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_ARGB(0, 0, 0, 0), 1.0f, 0);
	g_pD3d9Device->Clear(0, NULL, D3DCLEAR_ZBUFFER, D3DCOLOR_ARGB(0, 0, 0, 0), 1.0f, 0);
	g_pD3d9Device->BeginScene();

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
	g_pD3d9Device->SetTransform(D3DTS_WORLDMATRIX(0), &MatRotateX);
	// �󶨶��㻺�嵽�豸������
	g_pD3d9Device->SetStreamSource(0, g_pVertexBuffer, 0, sizeof(MY_VERTEX_TYPE));

	// ���ù���������������һ��Direct3D��������������ͼƬ��ƽ����������������������������
	g_pD3d9Device->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR); 
	g_pD3d9Device->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);   

	// ��������
	g_pD3d9Device->SetTexture(0, g_pTexture);

	// ����3D��Ⱦģʽ
	// �ӵ�0���㿪ʼ�� D3DPT_TRIANGLESTRIP ģʽ��Ⱦ2��������
	g_pD3d9Device->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

	g_pD3d9Device->EndScene();
	// ����ǰ�󻺳�
	g_pD3d9Device->Present(NULL, NULL, NULL, NULL);
}

void CleanupD3d9()
{
	RELEASE_COM_OBJECT(g_pVertexBuffer);
	RELEASE_COM_OBJECT(g_pTexture);
	RELEASE_COM_OBJECT(g_pD3d9Surface);
	RELEASE_COM_OBJECT(g_pD3d9);
	RELEASE_COM_OBJECT(g_pD3d9Device);
}

void RestoreSurfaces(HWND hWnd)
{
	CleanupD3d9();
	InitD3d9Device(hWnd);
}
