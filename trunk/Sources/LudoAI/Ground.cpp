///////////////////////////////
// Filename: Ground.cpp
// Description: Ground Object
// Creation Date: 14/01/2008
///////////////////////////////
#include "LudoCore/LudoGlobal.h"
#include "Ground.h"
#include "LudoCore/LudoVector.h"
#include "LudoRenderer/LudoRenderer.h"
#include "LudoCore/LudoStringManager.h"

static const float GROUND_POSITION_X = 0;
static const float GROUND_POSITION_Z = 0;
static const float GROUND_POSITION_Y = GROUND_POS;
static const float GROUND_SIZE_X = 4000.0f;
static const float GROUND_SIZE_Z = 4000.0f;
static const int GROUND_SAMPLING = 10;

Ground::Ground(std::wstring baseName) : GameObject(baseName)
{
    m_Position = LUDO_NEW LudoVector();
}

Ground::~Ground()
{
    LUDO_SAFE_RELEASE(m_GroundTexture);
    LUDO_SAFE_DELETE(m_Position);
}

// Virtual
void Ground::Init()
{
    for (int i = 0; i < GROUND_NUM_VERTICES; i++)
    {
        m_GroundVertices[i].nx = 0;
        m_GroundVertices[i].ny = 1;
        m_GroundVertices[i].nz = 0;
        m_GroundVertices[i].y = GROUND_POSITION_Y;  
    }

    // Prepare textures and vertices here...    
    m_GroundVertices[0].x = GROUND_POSITION_X - GROUND_SIZE_X / 2.0f;
    m_GroundVertices[0].z = GROUND_POSITION_Z - GROUND_SIZE_Z / 2.0f;
    m_GroundVertices[0].u = 0;
    m_GroundVertices[0].v = 0;

    m_GroundVertices[1].x = GROUND_POSITION_X + GROUND_SIZE_X / 2.0f;
    m_GroundVertices[1].z = GROUND_POSITION_Z - GROUND_SIZE_Z / 2.0f;
    m_GroundVertices[1].u = GROUND_SAMPLING;
    m_GroundVertices[1].v = 0;

    m_GroundVertices[2].x = GROUND_POSITION_X - GROUND_SIZE_X / 2.0f;
    m_GroundVertices[2].z = GROUND_POSITION_Z + GROUND_SIZE_Z / 2.0f;
    m_GroundVertices[2].u = 0;
    m_GroundVertices[2].v = GROUND_SAMPLING;

    m_GroundVertices[3].x = GROUND_POSITION_X + GROUND_SIZE_X / 2.0f;
    m_GroundVertices[3].z = GROUND_POSITION_Z + GROUND_SIZE_Z / 2.0f;
    m_GroundVertices[3].u = GROUND_SAMPLING;
    m_GroundVertices[3].v = GROUND_SAMPLING;


    D3DXIMAGE_INFO textureInfo;
    D3DXCreateTextureFromFileEx( LudoRenderer::GetInstance()->GetDevice(), LudoStringManager::GetInstance()->GetString(GROUND_TEXTURE).c_str(), D3DX_DEFAULT, D3DX_DEFAULT, D3DX_DEFAULT, 0, 
        D3DFMT_A8R8G8B8, D3DPOOL_MANAGED, D3DX_DEFAULT, D3DX_DEFAULT, 0, &textureInfo, NULL, (IDirect3DTexture9**)&m_GroundTexture );

    GameObject::Init();
}

// Virtual
void Ground::Update()
{
    GameObject::Update();
}

// Virtual
void Ground::Render()
{
    // Do your draw call here
    LudoRenderer::GetInstance()->DrawVertices(*m_GroundVertices,GROUND_NUM_VERTICES,NULL,0,m_GroundTexture);

    GameObject::Render();
}
