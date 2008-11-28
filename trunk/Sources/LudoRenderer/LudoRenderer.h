#pragma once
#include <d3d9.h>
#include "External/DirectXSDK/Include/d3dx9mesh.h"
#include "LudoCore/Singleton.h"

// include the Direct3D Library files
#pragma comment (lib, "../External/PlatformSDK/Lib/d3d9.lib")
#pragma comment (lib, "../External/DirectXSDK/Lib/d3dx9.lib")
#pragma comment (lib, "../External/DirectXSDK/Lib/dxerr9.lib")
#pragma comment (lib, "../External/DirectXSDK/Lib/dxerr.lib")

#define CUSTOMFVF (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX1)
struct CUSTOMVERTEX 
{
    float x;
    float y;
    float z;
    float nx;
    float ny;
    float nz;
    float u;
    float v;
};

class LudoCamera;

class LudoRenderer : public Singleton<LudoRenderer>
{
    friend class Singleton<LudoRenderer>;

protected:
    HWND                                    m_hWnd;

    IDirect3D9*                             m_pD3D;
    IDirect3DDevice9*                       m_pD3DDevice;
    D3DPRESENT_PARAMETERS                   m_D3Dpp;
    D3DFORMAT                               m_Format;

    int                                     m_Width;
    int                                     m_Height;

public:
    bool                Init( HWND hWnd, int Width, int Height );
    bool                DrawVertices(CUSTOMVERTEX &vertices, int numVertices, int *indices, int numIndices, LPDIRECT3DTEXTURE9 texture);
    void                SwitchWireframeDisplayMode();

    bool                BeginScene();
    bool                EndScene();

    IDirect3DDevice9 *  GetDevice();
    void                SetCamera(LudoCamera *camera);

private:
    LudoRenderer();
    ~LudoRenderer();

    bool DrawQuad(float x1, float y1, float z1, float x2, float y2, float z2, float x3, float y3, float z3, float x4, float y4, float z4, LPDIRECT3DTEXTURE9 texture);

    bool CreateVertexBuffer(int numVertices);
    bool CreateIndexBuffer(int numIndices);
    bool ConfigureScene();
    bool ConfigureViewport(float fieldOfView, int width, int height, float nearPlane, float farPlane);

    IDirect3D9 *m_d3d;
    IDirect3DDevice9 *m_d3DDev;

    LPDIRECT3DVERTEXBUFFER9 m_VertBuff;
    LPDIRECT3DINDEXBUFFER9 m_IndexBuff;

    LudoCamera* m_Camera;

    int             m_MaxNumVertex;
    int             m_MaxNumIndices;
    bool            m_WireframeMode;
};
