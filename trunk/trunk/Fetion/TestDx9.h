
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
��   һ��ʼ��ģ�ʹ������Լ��ľֲ�����ռ��ڣ� 

��   ����World   Transform��ģ�ͱ任�������� 
��ռ�(world   space)�� 

��   Ȼ������View   Transform��ģ�ͱ任���ӵ� 
����ռ�(eye   space,   or   camera   space)�� 

��   Ȼ����Projection   Transform���ӵ�ռ�任��һ�� 
���ĵ���ԭ�㣬�߳�Ϊ2��������ռ䡣 

��   ���ͨ����direct3d��viewport�任�������IDirect3D::SetViewport()�� 
ת������Ļ���ꡣ 

ͨ������SetTransform()���޸���Щ�任���� 
�Ϳ��Բ�����ά������Ч���� 
*/
