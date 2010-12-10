
#pragma once

#include <atltypes.h>
#include <d3d9.h>
#include <d3dx9math.h>
#include "BitmapDC.h"

class CDxD3DRender
{
public:
	CDxD3DRender();
	virtual ~CDxD3DRender();

	bool IsInit() { return (m_pD3d9 != NULL); };
	void InitD3d9Device(HWND hWnd, HBITMAP hBmp);
	void D3dRender();
	void CleanupD3d9();

	HDC GetD3dRenderTargetData();

private:
	void CreateTextureFromHBITMAP(HBITMAP hBmp);
	void InitDrawGraphics();

private:
	LPDIRECT3D9 m_pD3d9;
	LPDIRECT3DDEVICE9 m_pD3d9Device;
	LPDIRECT3DVERTEXBUFFER9 m_pVertexBuffer;
	LPDIRECT3DTEXTURE9 m_pTexture;
	LPDIRECT3DSURFACE9 m_pD3dTargetSurface;
	LPDIRECT3DSURFACE9 m_pSysSurface;

	CRect m_RenderRect;
	// ��ת��DC
	CBitmapDC m_RgnBmpDc;
};





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
