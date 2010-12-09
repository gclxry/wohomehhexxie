
#pragma once

#include <atltypes.h>
#include <d3d9.h>
#include <d3dx9math.h>

extern LPDIRECT3D9 g_pD3d9;                       //Pointer to our Direct3D interface
extern LPDIRECT3DDEVICE9 g_pD3d9Device;              //Pointer to the g_pD3d9Device class
extern LPDIRECT3DVERTEXBUFFER9 vertex_buffer; //The pointer to the vertex buffer
extern LPDIRECT3DTEXTURE9 texture_1;          //Texture for single large solid
extern LPDIRECT3DTEXTURE9 top_bottom_texture;
extern IDirect3DSurface9 * mesh; 


//g_pD3d9
// This function initializes and prepares Direct3D for use
void InitD3d9Device(HWND hWnd);

// This is the function used to render a single frame
void render();

// This is the function that cleans up Direct3D and COM
void cleanup();

// This is the function that defines the 3D cube
void InitDrawGraphics();

// Gets called after we leave then return to this program; handled by
//  throwing away our old COM objects and re-doing initialization
void restore_surfaces(HWND hWnd);
