
#pragma once

#include <atltypes.h>
#include <d3d9.h>
#include <d3dx9math.h>

extern LPDIRECT3D9 g_pD3d9;
extern LPDIRECT3DDEVICE9 g_pD3d9Device;
extern LPDIRECT3DVERTEXBUFFER9 g_pVertexBuffer;
extern LPDIRECT3DTEXTURE9 g_pTexture;
extern IDirect3DSurface9 * g_pD3d9Surface;


void InitD3d9Device(HWND hWnd);
void Render();
void CleanupD3d9();
void RestoreSurfaces(HWND hWnd);


/*
●   一开始，模型处在他自己的局部坐标空间内； 

●   先用World   Transform把模型变换到世界坐 
标空间(world   space)； 

●   然后再用View   Transform把模型变换到视点 
坐标空间(eye   space,   or   camera   space)； 

●   然后用Projection   Transform把视点空间变换成一个 
中心点在原点，边长为2的立方体空间。 

●   最后通过的direct3d的viewport变换（详见：IDirect3D::SetViewport()） 
转换成屏幕坐标。 

通过调用SetTransform()来修改这些变换矩阵， 
就可以产生三维动画的效果。 
*/
