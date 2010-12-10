
#include "stdafx.h"
#include "TestDx9.h"


#define RELEASE_COM_OBJECT(obj)					{if((obj) != NULL) {(obj)->Release(); (obj) = NULL;}}
// 顶点格式
#define CUSTOMFVF								(D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX1)

// 自定义顶点格式
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
/*	// --------- 从文件创建纹理
	HRESULT hRet = D3DXCreateTextureFromFileEx(
		m_pD3d9Device, 
		_T("D:\\TestSkin\\textwrap.bmp"), 
		m_RenderRect.Width(), m_RenderRect.Height(),
		D3DX_DEFAULT, D3DUSAGE_RENDERTARGET, 
		D3DFMT_X8R8G8B8, D3DPOOL_DEFAULT,    
		D3DX_DEFAULT, D3DX_DEFAULT, 0, NULL, NULL,
		&m_pTexture);*/

	// 渲染顶点样例
	MY_VERTEX_TYPE DemoVertices[] =
	{
		{ -5.0f, 5.0f, -5.0f, 0, 0, -1, 0, 0 },
		{ 5.0f, 5.0f, -5.0f, 0, 0, -1, 1, 0 },
		{ -5.0f, -5.0f, -5.0f, 0, 0, -1, 0, 1 },
		{ 5.0f, -5.0f, -5.0f, 0, 0, -1, 1, 1 },
	};

	// 创建一个能容纳24个顶点数据的buffer
	m_pD3d9Device->CreateVertexBuffer(24 * sizeof(MY_VERTEX_TYPE), 0,
		CUSTOMFVF, D3DPOOL_MANAGED, &m_pVertexBuffer, NULL);

	// 设置顶点数据
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
	// 初始化D3d设备
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






	// 初始化绘图内容
	CreateTextureFromHBITMAP(hBmp);
	InitDrawGraphics();

//////////////////////////////////////////////////////////////////////////
	// 设置渲染状态

	// 关闭光照效果
	m_pD3d9Device->SetRenderState(D3DRS_LIGHTING, FALSE);
	// 启用深度测试
	m_pD3d9Device->SetRenderState(D3DRS_ZENABLE, TRUE);
	// 不剔除任何面（D3DCULL_NONE：图片背面也渲染）
	m_pD3d9Device->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

//////////////////////////////////////////////////////////////////////////
	// 设置视觉矩阵（摄像机矩阵 D3DTS_VIEW）

	// 视觉改变矩阵
	D3DXMATRIX MatView;
	// 摄像机点（眼球位置）
	D3DXVECTOR3 CameraVct(0.0f, 0.0f, -19.5f);
	// 观察点，目标位置向量
	D3DXVECTOR3 LookatVct(0.0f, 0.0f, 0.0f);
	// 当前世界坐标系向上方向向量
	D3DXVECTOR3 UpVct(0.0f, 1.0f, 0.0f);
	// 设置观察矩阵
	D3DXMatrixLookAtLH(&MatView, &CameraVct, &LookatVct, &UpVct);
	// 设置变换矩阵
	m_pD3d9Device->SetTransform(D3DTS_VIEW, &MatView);

//////////////////////////////////////////////////////////////////////////
	// 设置Z轴投影矩阵（透视矩阵 D3DTS_PROJECTION）

	// Z轴投影操作矩阵
	D3DXMATRIX MatZProjection;  

	// 创建一个左手坐标系的透视投影矩阵
	// 参数一：指向D3DXMATRIX 结构的操作结果矩阵。
	// 参数二：观察时y轴方向的角度（弧度），就是观察范围夹角。
	// 参数三：纵横比，在视空间宽度除以高度。
	// 参数四：近裁剪面位置Z值。
	// 参数五：远裁剪面位置Z值。
	D3DXMatrixPerspectiveFovLH(&MatZProjection, D3DXToRadian(45.0f),  
		(FLOAT)m_RenderRect.Width() / (FLOAT)m_RenderRect.Height(), 0.0f, 100.0f);   

	m_pD3d9Device->SetTransform(D3DTS_PROJECTION, &MatZProjection);

	// 设置固定渲染管道的顶点格式
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

	// 用指定的绕Y轴角度，绕X轴角度和Z轴角度创建旋转矩阵
	// 参数一：指向D3DXMATRIX结构的操作结果矩阵
	// 参数二：绕着Y轴旋转角度（单位弧度）
	// 参数三：绕着X轴旋转角度（单位弧度）
	// 参数四：绕着Z轴旋转角度（单位弧度）
	// 这个矩阵的变换顺序是先绕着Z轴旋转，接着是绕着X轴旋转，最后是绕着Y轴旋转。这些都是相对于物体的本地坐标系来说的
	D3DXMatrixRotationYawPitchRoll(&MatRotateX, sfIndex, sfIndex / (float)4.0, sfIndex / (float)4.0);

	// 设置世界坐标
	m_pD3d9Device->SetTransform(D3DTS_WORLDMATRIX(0), &MatRotateX);
	// 绑定顶点缓冲到设备数据流
	m_pD3d9Device->SetStreamSource(0, m_pVertexBuffer, 0, sizeof(MY_VERTEX_TYPE));

	// 设置过滤器（过滤器是一种Direct3D用它来帮助变形图片的平滑技术），第三个参数即过滤器
	m_pD3d9Device->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR); 
	m_pD3d9Device->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);   

	// 设置纹理
	m_pD3d9Device->SetTexture(0, m_pTexture);

	// 设置3D渲染模式
	// 从第0个点开始用 D3DPT_TRIANGLESTRIP 模式渲染2个三角形
	m_pD3d9Device->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

	m_pD3d9Device->EndScene();
	// 交换前后缓冲
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
