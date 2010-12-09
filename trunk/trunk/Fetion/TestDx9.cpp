
#include "stdafx.h"
#include "TestDx9.h"

LPDIRECT3D9 g_pD3d9 = NULL;
LPDIRECT3DDEVICE9 g_pD3d9Device = NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVertexBuffer = NULL;
LPDIRECT3DTEXTURE9 g_pTexture = NULL;
IDirect3DSurface9 *g_pD3d9Surface = NULL; 

#define RELEASE_COM_OBJECT(obj)					{if((obj) != NULL) {(obj)->Release(); (obj) = NULL;}}
// 顶点格式
#define CUSTOMFVF								(D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX1)

struct MY_VERTEX_TYPE
{
	FLOAT X, Y, Z;
	D3DVECTOR NORMAL;
	FLOAT U, V;
};

void InitDrawGraphics()
{
	// --------- 从文件创建纹理
	HRESULT hRet = D3DXCreateTextureFromFileEx(
		g_pD3d9Device, 
		_T("D:\\TestSkin\\textwrap.bmp"), 
		512,
		512, 
		D3DX_DEFAULT, D3DUSAGE_RENDERTARGET, 
		D3DFMT_X8R8G8B8, D3DPOOL_DEFAULT,    
		D3DX_DEFAULT, D3DX_DEFAULT, 0, NULL, NULL,
		&g_pTexture);

	// 渲染顶点样例
	MY_VERTEX_TYPE DemoVertices[] =
	{
		{ -5.0f, 5.0f, -5.0f, 0, 0, -1, 0, 0 },
		{ 5.0f, 5.0f, -5.0f, 0, 0, -1, 1, 0 },
		{ -5.0f, -5.0f, -5.0f, 0, 0, -1, 0, 1 },
		{ 5.0f, -5.0f, -5.0f, 0, 0, -1, 1, 1 },
	};

	// 创建一个能容纳24个顶点数据的buffer
	hRet = g_pD3d9Device->CreateVertexBuffer(24 * sizeof(MY_VERTEX_TYPE), 0,
		CUSTOMFVF, D3DPOOL_MANAGED, &g_pVertexBuffer, NULL);

	// 设置顶点数据
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
	// 初始化D3d设备
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

	// 初始化绘图内容
	InitDrawGraphics();

//////////////////////////////////////////////////////////////////////////
	// 设置渲染状态

	// 关闭光照效果
	g_pD3d9Device->SetRenderState(D3DRS_LIGHTING, FALSE);
	// 启用深度测试
	g_pD3d9Device->SetRenderState(D3DRS_ZENABLE, TRUE);
	// 不剔除任何面（D3DCULL_NONE：图片背面也渲染）
	g_pD3d9Device->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

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
	g_pD3d9Device->SetTransform(D3DTS_VIEW, &MatView);

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
		(FLOAT)ClientRect.Width() / (FLOAT)ClientRect.Height(), 0.0f, 100.0f);   

	g_pD3d9Device->SetTransform(D3DTS_PROJECTION, &MatZProjection);

	// 设置固定渲染管道的顶点格式
	g_pD3d9Device->SetFVF(CUSTOMFVF);

	// 取得用于渲染的纹理表面
	g_pD3d9Device->CreateOffscreenPlainSurface(512, 512, D3DFMT_A8R8G8B8, D3DPOOL_DEFAULT, &g_pD3d9Surface, NULL);

	// --------- 从文件创建纹理表面
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

	// 用指定的绕Y轴角度，绕X轴角度和Z轴角度创建旋转矩阵
	// 参数一：指向D3DXMATRIX结构的操作结果矩阵
	// 参数二：绕着Y轴旋转角度（单位弧度）
	// 参数三：绕着X轴旋转角度（单位弧度）
	// 参数四：绕着Z轴旋转角度（单位弧度）
	// 这个矩阵的变换顺序是先绕着Z轴旋转，接着是绕着X轴旋转，最后是绕着Y轴旋转。这些都是相对于物体的本地坐标系来说的
	D3DXMatrixRotationYawPitchRoll(&MatRotateX, sfIndex, sfIndex / (float)4.0, sfIndex / (float)4.0);

	// 设置世界坐标
	g_pD3d9Device->SetTransform(D3DTS_WORLDMATRIX(0), &MatRotateX);
	// 绑定顶点缓冲到设备数据流
	g_pD3d9Device->SetStreamSource(0, g_pVertexBuffer, 0, sizeof(MY_VERTEX_TYPE));

	// 设置过滤器（过滤器是一种Direct3D用它来帮助变形图片的平滑技术），第三个参数即过滤器
	g_pD3d9Device->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR); 
	g_pD3d9Device->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);   

	// 设置纹理
	g_pD3d9Device->SetTexture(0, g_pTexture);

	// 设置3D渲染模式
	// 从第0个点开始用 D3DPT_TRIANGLESTRIP 模式渲染2个三角形
	g_pD3d9Device->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

	g_pD3d9Device->EndScene();
	// 交换前后缓冲
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
