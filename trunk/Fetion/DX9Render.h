
#pragma once

#include <d3d9.h>
#pragma warning( disable : 4996 ) // disable deprecated warning 

#include <strsafe.h>
#pragma warning( default : 4996 )

extern LPDIRECT3D9         g_pD3D; // Used to create the D3DDevice
extern LPDIRECT3DDEVICE9   g_pd3dDevice; // Our rendering g_pD3d9Device


//-----------------------------------------------------------------------------
// Name: InitD3D()
// Desc: Initializes Direct3D
//-----------------------------------------------------------------------------
HRESULT InitD3D( HWND hWnd );

//-----------------------------------------------------------------------------
// Name: Cleanup()
// Desc: Releases all previously initialized objects
//-----------------------------------------------------------------------------
VOID Cleanup();



