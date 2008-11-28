///////////////////////////////
// Filename: LudoRenderer.cpp
// Description:
// Creation Date: 31/10/2007
///////////////////////////////
#include "LudoCore/LudoGlobal.h"
#include <math.h>
#include "LudoRenderer.h"
#include "LudoCamera.h"
#include "LudoCore/LudoStringManager.h"

const static int DEFAULT_NUM_VERTEX = 4;
const static float DEFAULT_VIEW_ANGLE = 45.0f;
const static float DEFAULT_NEAR_PLANE = 0.01f;
const static float DEFAULT_FAR_PLANE = 100000.0f;
LudoRenderer::LudoRenderer() :
    m_d3d(NULL),
    m_d3DDev(NULL),
    m_VertBuff(NULL),   
    m_IndexBuff(NULL),
    m_Camera(NULL),
    m_MaxNumVertex(0),
    m_MaxNumIndices(0),
    m_WireframeMode(false)
{

}

LudoRenderer::~LudoRenderer()
{
    LUDO_SAFE_RELEASE(m_VertBuff);
    LUDO_SAFE_RELEASE(m_IndexBuff);
    LUDO_SAFE_RELEASE(m_d3DDev);
    LUDO_SAFE_RELEASE(m_d3d);
}

bool LudoRenderer::Init(HWND windowHandle, int width, int height)
{
    // Here, there should be error checking!
    m_d3d = Direct3DCreate9(D3D_SDK_VERSION);

    D3DDISPLAYMODE d3ddm;
    m_d3d->GetAdapterDisplayMode( 0, &d3ddm );

    D3DPRESENT_PARAMETERS d3dpp;
    ZeroMemory(&d3dpp, sizeof(d3dpp));
    d3dpp.Windowed = TRUE;
    d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD; 	
    d3dpp.hDeviceWindow = windowHandle; 	
    d3dpp.BackBufferFormat = d3ddm.Format;
    d3dpp.BackBufferCount = 1; 		      
    d3dpp.EnableAutoDepthStencil  = TRUE;
    d3dpp.AutoDepthStencilFormat  = D3DFMT_D24X8;  

    m_d3d->CreateDevice ( D3DADAPTER_DEFAULT,   // Default adapter 
        D3DDEVTYPE_HAL,                         // Default type
        windowHandle,                           // handle to your window
        D3DCREATE_SOFTWARE_VERTEXPROCESSING,    // Using software vertex processing
        &d3dpp,                                 // your parameters
        &m_d3DDev);                             // Pointer to the created device. 

    ConfigureScene();

    ConfigureViewport(DEFAULT_VIEW_ANGLE, width, height, DEFAULT_NEAR_PLANE, DEFAULT_FAR_PLANE);

    return true;
}

bool LudoRenderer::CreateVertexBuffer(int numVertices)
{
    LUDO_SAFE_RELEASE(m_VertBuff);
    
    m_MaxNumVertex = numVertices;

    m_d3DDev->CreateVertexBuffer(numVertices * sizeof(CUSTOMVERTEX),
        NULL,
        CUSTOMFVF,
        D3DPOOL_MANAGED,
        &m_VertBuff,
        NULL);

    // select which vertex format we are using
    m_d3DDev->SetFVF(CUSTOMFVF);

    // select the vertex buffer to display
    m_d3DDev->SetStreamSource(0, m_VertBuff, 0, sizeof(CUSTOMVERTEX));
    return true;
}

bool LudoRenderer::CreateIndexBuffer(int numIndices)
{
    LUDO_SAFE_RELEASE(m_IndexBuff);

    m_MaxNumIndices = numIndices;
    m_d3DDev->CreateIndexBuffer( numIndices * sizeof( int ), 
        0, 
        D3DFMT_INDEX32,
        D3DPOOL_MANAGED, 
        &m_IndexBuff, 
        NULL);
    m_d3DDev->SetIndices(m_IndexBuff);

    return true;
}

bool LudoRenderer::ConfigureScene()
{ 
    m_d3DDev->SetRenderState( D3DRS_LIGHTING, FALSE);
    m_d3DDev->SetRenderState( D3DRS_ZENABLE, TRUE );           // Enable Z ordering (3D)
    m_d3DDev->SetRenderState( D3DRS_FILLMODE, D3DFILL_SOLID ); // Your model should be filled (not wired)
    m_d3DDev->SetRenderState( D3DRS_CULLMODE, D3DCULL_NONE );  // disable to render both side of a triangle.

    m_d3DDev->SetSamplerState( 0, D3DSAMP_MAGFILTER,    D3DTEXF_LINEAR ); // Use for interpolation of texture
    m_d3DDev->SetSamplerState( 0, D3DSAMP_MINFILTER,    D3DTEXF_LINEAR );
    m_d3DDev->SetSamplerState( 0, D3DSAMP_MIPFILTER,    D3DTEXF_LINEAR );

    //enable texture tiling
    m_d3DDev->SetSamplerState( 0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP ); 
    m_d3DDev->SetSamplerState( 0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP );

    return true;
}

bool LudoRenderer::ConfigureViewport(float fieldOfView, int width, int height, float nearPlane, float farPlane)
{   
    D3DXMATRIX matProjection;                       // the projection transform matrix
    D3DXMatrixPerspectiveFovLH(&matProjection,
        D3DXToRadian(fieldOfView),                  // the horizontal field of view
        (float)width / (float)height,               // the aspect ratio
        nearPlane,                                  // the near view-plane
        farPlane);                                  // the far view-plane
    m_d3DDev->SetTransform(D3DTS_PROJECTION, &matProjection);    // set the projection

    D3DXMATRIX matWorld;                              // a matrix to store the rotation for each triangle
    D3DXMatrixRotationY(&matWorld, 0.0f);             // the rotation matrix
    m_d3DDev->SetTransform(D3DTS_WORLD, &(matWorld)); // set the world transform

    return true;
}

bool LudoRenderer::BeginScene()
{
    if (m_Camera != NULL)
    {
        D3DXMATRIX mat = m_Camera->GetMatrix();
        m_d3DDev->SetTransform(D3DTS_VIEW, &mat);   // set the view transform to matView
    }

    m_d3DDev->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);
    m_d3DDev->BeginScene();

    return true;
}

bool LudoRenderer::EndScene()
{
    m_d3DDev->EndScene();
    m_d3DDev->Present(NULL,NULL,NULL,NULL);
    return true;
}

bool LudoRenderer::DrawQuad(float x1, float y1, float z1, float x2, float y2, float z2, float x3, float y3, float z3, float x4, float y4, float z4, LPDIRECT3DTEXTURE9 texture)
{
    // Drawing a simple quad
    struct CUSTOMVERTEX t_vert[] =
    {
        // bottom right
        { x1, y1, z1, 0, 0, -1, 1, 1 },
        // bottom left
        { x2, y2, z2, 0, 0, -1, 0, 1},
        // top right
        { x3, y3, z3, 0, 0, -1, 1, 0},
        //top leff
        { x4, y4, z4, 0, 0, -1, 0, 0}
    };

    DrawVertices(*t_vert, 4, NULL, 0, texture);
    return true;
}

bool LudoRenderer::DrawVertices(CUSTOMVERTEX &vertices, int numVertices, int *indices, int numIndices, LPDIRECT3DTEXTURE9 texture)
{
    if (numIndices > m_MaxNumIndices)
    {
        CreateIndexBuffer(numIndices);
    }

    if (numVertices > m_MaxNumVertex)
    {
        CreateVertexBuffer(numVertices);
    }

    m_d3DDev->SetTexture( 0, texture );

    VOID* pVoid = 0;
    m_VertBuff->Lock(0, 0, (void**)&pVoid, NULL);
    memcpy_s(pVoid, sizeof(CUSTOMVERTEX) * numVertices, (BYTE**)&vertices, sizeof(CUSTOMVERTEX) * numVertices);
    m_VertBuff->Unlock();

    if (indices == NULL)
    {
        m_d3DDev->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, numVertices - 2);
    }
    else
    {
        void* buffer = NULL;
        m_IndexBuff->Lock(0, 0, &buffer, NULL);
        memcpy_s(buffer, numIndices * sizeof(int), indices, numIndices * sizeof(int));
        m_IndexBuff->Unlock();

        m_d3DDev->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, numVertices, 0, numIndices - 2);
    }

    
    return true;
}

IDirect3DDevice9 * LudoRenderer::GetDevice()
{
    return m_d3DDev;
}

void LudoRenderer::SwitchWireframeDisplayMode()
{
    m_WireframeMode = !m_WireframeMode;
    if (m_WireframeMode)
    {
        m_d3DDev->SetRenderState( D3DRS_FILLMODE, D3DFILL_WIREFRAME );
    }
    else
    {
        m_d3DDev->SetRenderState( D3DRS_FILLMODE, D3DFILL_SOLID );
    }
}

void LudoRenderer::SetCamera(LudoCamera *camera)
{
    m_Camera = camera;
}