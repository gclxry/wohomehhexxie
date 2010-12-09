
#include "stdafx.h"
#include "TestDx9.h"

LPDIRECT3D9 g_pD3d9;                       // Direct3D interface
LPDIRECT3DDEVICE9 g_pD3d9Device;              // Device class
LPDIRECT3DVERTEXBUFFER9 vertex_buffer; // Vertex buffer
LPDIRECT3DTEXTURE9 texture_1;          // Texture for single large solid
IDirect3DSurface9 * mesh; 

#define RELEASE_COM_OBJECT(i) if(i!=NULL&& i) i->Release();
struct MYVERTEXTYPE {FLOAT X, Y, Z; D3DVECTOR NORMAL; FLOAT U, V;};
#define CUSTOMFVF (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX1)

#define CUBE_ACCEL 1.0025
#define CUBE_START_SPEED 0.02
#define CUBE_MAX_SPEED 0.10
#define CAMERA_DISTANCE 19.5
#define AMBIENT_BRIGHTNESS 140
#define TEXTURE_SIZE 512 //NEW VALUE
#define VERTICAL_VIEWFIELD_DEGREES 45.0
#define FRUSTUM_NEAR_Z 1.0f
#define FRUSTUM_FAR_Z 100.0f
#define LIGHT_DISTANCE 40.0f
#define LIGHT_RANGE 60.0f
#define LIGHT_CONE_RADIANS_INNER 0.405f; 
#define LIGHT_CONE_RADIANS_OUTER 0.425f; 
#define TEXTURE_FILE_NAME _T("textwrap.bmp")
#define CUBE_VERTICES 24
#define DEMO_TEXT_COLOR  D3DCOLOR_ARGB(255,108,108,228)
#define TEXT_SCROLL_SPEED 5
#define TEXT_POINTS 70
#define TEXT_TOP 210  

// 初始化D3d设备
void InitD3d9Device(HWND hWnd)
{
	CRect ClientRect;
	::GetClientRect(hWnd, ClientRect);

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

	g_pD3d9->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL,
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

	// 视觉改变矩阵
	D3DXMATRIX MatView;    // the view transform matrix

	// 摄像机（眼球）点
	D3DXVECTOR3 CameraVct(0.0f, 0.0f, -CAMERA_DISTANCE);
	// 观察点
	D3DXVECTOR3 LookatVct(0.0f, 0.0f, 0.0f);
	// 头顶方向点
	D3DXVECTOR3 UpVct(0.0f, 1.0f, 0.0f);

	D3DXMatrixLookAtLH(&MatView, &CameraVct, &LookatVct, &UpVct);

	g_pD3d9Device->SetTransform(D3DTS_VIEW, &MatView);

	// This is the projection transform.. the last parameter to the call 
	// is the point in positive Z-dimension that things become invisible
	D3DXMATRIX matProjection;  

	D3DXMatrixPerspectiveFovLH
		(&matProjection,
		D3DXToRadian(VERTICAL_VIEWFIELD_DEGREES),  
		(FLOAT)ClientRect.Width() / (FLOAT)ClientRect.Height(), 
		FRUSTUM_NEAR_Z,     //Defined near top of file    
		FRUSTUM_FAR_Z);   

	g_pD3d9Device->SetTransform(D3DTS_PROJECTION, &matProjection);

	g_pD3d9Device->SetFVF(CUSTOMFVF);

	//Create "mesh"... the basic background layer of the texture 
	g_pD3d9Device->CreateOffscreenPlainSurface 
		(TEXTURE_SIZE, TEXTURE_SIZE, D3DFMT_X8R8G8B8, D3DPOOL_DEFAULT, &mesh,
		NULL);

	//Scales from basis size to texture size if necess.
	D3DXLoadSurfaceFromFile
		(mesh, NULL, NULL, TEXTURE_FILE_NAME,NULL,
		D3DX_DEFAULT, 0, NULL);

}

// This is the function used to render a single frame
void render()
{

	static float index = 0.0 ;

	//Clear output buffer and vertex buffer 
	g_pD3d9Device->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);
	g_pD3d9Device->Clear(0, NULL, D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);

	g_pD3d9Device->BeginScene();

	//NEW call
	//do_2D_work ();

	//
	//Index is used to spin the main cube... a rotation of index is applied in
	// each dimension to make things interesting
	//
	static float speed = CUBE_START_SPEED;
	speed *= CUBE_ACCEL;

	if(speed>CUBE_MAX_SPEED) speed=CUBE_MAX_SPEED;

	index+=speed;  

	D3DXMATRIX matRotateX;

	//We rotate 4x faster in Yaw to show off scrolling text at start 
	D3DXMatrixRotationYawPitchRoll (&matRotateX, index, index / 4.0,
		index / 4.0);

	// Set the world transform
	g_pD3d9Device->SetTransform(D3DTS_WORLDMATRIX(0), &(matRotateX));    
	g_pD3d9Device->SetStreamSource(0, vertex_buffer, 0, sizeof(MYVERTEXTYPE));

	g_pD3d9Device->SetSamplerState (0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR); 
	g_pD3d9Device->SetSamplerState (0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);   

	g_pD3d9Device->SetTexture (0, texture_1);

	g_pD3d9Device->DrawPrimitive (D3DPT_TRIANGLESTRIP, 0, 2);

	g_pD3d9Device->EndScene(); 
	g_pD3d9Device->Present(NULL, NULL, NULL, NULL) ;
}

// This is the function that cleans up Direct3D and COM
void cleanup()
{
	RELEASE_COM_OBJECT(vertex_buffer)
		RELEASE_COM_OBJECT(texture_1)
		RELEASE_COM_OBJECT(mesh)
		RELEASE_COM_OBJECT(g_pD3d9)    
		RELEASE_COM_OBJECT(g_pD3d9Device)  
}

// This is the function that defines the 3D cube
void InitDrawGraphics()
{

	D3DXCreateTextureFromFileEx (
		g_pD3d9Device, 
		TEXTURE_FILE_NAME, 
		TEXTURE_SIZE,
		TEXTURE_SIZE, 
		D3DX_DEFAULT, D3DUSAGE_RENDERTARGET, 
		D3DFMT_X8R8G8B8, D3DPOOL_DEFAULT,    
		D3DX_DEFAULT, D3DX_DEFAULT, 0, NULL, NULL,
		&texture_1 
		);

	//
	// This defines the shape of our single large polyhedron
	//
	MYVERTEXTYPE demo_vertices[] =
	{
		//
		//Each of these groups-of-four is a face of our solid
		//
		{ -5.0f, 5.0f, -5.0f, 0, 0, -1, 0, 0 },  // Front face  
		{ 5.0f, 5.0f, -5.0f, 0, 0, -1, 1, 0 },
		{ -5.0f, -5.0f, -5.0f, 0, 0, -1, 0, 1 },
		{ 5.0f, -5.0f, -5.0f, 0, 0, -1, 1, 1 },

	};    

	// COM creation of vertex buffer
	g_pD3d9Device->CreateVertexBuffer(
		CUBE_VERTICES*sizeof(MYVERTEXTYPE),  //Cube has 24 vertices
		0,
		CUSTOMFVF,
		D3DPOOL_MANAGED,
		&vertex_buffer,
		NULL);

	VOID* pVoid;    

	// Lock vertex_buffer and load the vertices into it
	vertex_buffer->Lock(0, 0, (void**)&pVoid, 0);
	memcpy(pVoid, demo_vertices, sizeof(demo_vertices));
	vertex_buffer->Unlock();

}

void restore_surfaces(HWND hWnd)
{
	cleanup();   
	InitD3d9Device(hWnd);    
}
