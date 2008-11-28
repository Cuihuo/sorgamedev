///////////////////////////////
// Filename: Rail.cpp
///////////////////////////////
#include "LudoCore/LudoGlobal.h"
#include "Rail.h"
#include "LudoCore/LudoVector.h"
#include "LudoCore/LudoUtilities.h"
#include "LudoCore/LudoStringManager.h"

const static float RAIL_SCALE_FACTOR = 100.0f;
const static float RAIL_TICK_SCALE = 10.0f;
const static float RAIL_OFFSET_GROUND = 20.0f;


Rail::Rail(LudoVector* position, std::wstring baseName) : GameObject(baseName)
{
    m_Position = LUDO_NEW LudoVector(position->GetX(),position->GetY(),position->GetZ());

    m_Position->SetX(m_Position->GetX() * RAIL_SCALE_FACTOR);
    m_Position->SetY(m_Position->GetY() * RAIL_SCALE_FACTOR);
    m_Position->SetZ(m_Position->GetZ() * RAIL_SCALE_FACTOR);
    m_NextRail = NULL;
}

Rail::~Rail()
{
    LUDO_SAFE_DELETE(m_Position);
    LUDO_SAFE_RELEASE(m_RailTexture);
}

// Virtual
void Rail::Init()
{
    // Prepare texture and vertices
    if (m_NextRail)
    {
        D3DXIMAGE_INFO textureInfo;
        D3DXCreateTextureFromFileEx( LudoRenderer::GetInstance()->GetDevice(), LudoStringManager::GetInstance()->GetString(RAIL_TEXTURE).c_str(), D3DX_DEFAULT, D3DX_DEFAULT, D3DX_DEFAULT, 0, 
            D3DFMT_A8R8G8B8, D3DPOOL_MANAGED, D3DX_DEFAULT, D3DX_DEFAULT, 0, &textureInfo, NULL, (IDirect3DTexture9**)&m_RailTexture );

        LudoVector *nextRailPosition = m_NextRail->GetPosition();
        LudoVector *railVector = LUDO_NEW LudoVector();
        railVector->SetX(nextRailPosition->GetX() - m_Position->GetX());
        railVector->SetY(nextRailPosition->GetY() - m_Position->GetY());
        railVector->SetZ(nextRailPosition->GetZ() - m_Position->GetZ());
        float railLength = railVector->GetLength();

        for( int i = 0; i < RAIL_DEFINITION; i++)
        {
            FLOAT theta = (LUDO_2_PI * i) / (RAIL_DEFINITION - 1);

            int indexDown = 2 * i;
            m_RailVertices[indexDown].x        = sinf(theta);
            m_RailVertices[indexDown].y        = cosf(theta);
            m_RailVertices[indexDown].z        = -1.0f;
            m_RailVertices[indexDown].u       = ((FLOAT)i)/(RAIL_DEFINITION-1);
            m_RailVertices[indexDown].v       = 1.0f;
            m_RailIndices[indexDown] = indexDown;

            int indexUp = 2 * i + 1;
            m_RailVertices[indexUp].x        = sinf(theta);
            m_RailVertices[indexUp].y        = cosf(theta);
            m_RailVertices[indexUp].z        = 1.0f;
            m_RailVertices[indexUp].u       = ((FLOAT)i)/(RAIL_DEFINITION-1);
            m_RailVertices[indexUp].v       = 0.0f;
            m_RailIndices[indexUp] = indexUp;
        }

        m_Transformation.LoadIdentity();
        m_Transformation.Scale(RAIL_TICK_SCALE, RAIL_TICK_SCALE,railLength / 2.0f);


        float angle_a = asin(railVector->GetX()/railLength);
        m_Transformation.RotY(angle_a);

        float angle_b = atan2(railVector->GetY(),-railVector->GetZ());
        m_Transformation.RotX(angle_b);

        m_Transformation.Trans(m_Position->GetX() + railVector->GetX() / 2.0f,m_Position->GetY() + railVector->GetY() / 2.0f + GROUND_POS + RAIL_OFFSET_GROUND,m_Position->GetZ() + railVector->GetZ() / 2.0f);

        LUDO_DELETE(railVector);

    }

    GameObject::Init();
}

// Virtual
void Rail::Update()
{
    GameObject::Update();
}

// Virtual
void Rail::Render()
{
    // Render your object here
    D3DXMATRIX    CurrentMatrix;
    LudoRenderer::GetInstance()->GetDevice()->GetTransform( D3DTS_WORLD, &CurrentMatrix );
    LudoRenderer::GetInstance()->GetDevice()->SetTransform( D3DTS_WORLD, (D3DMATRIX*)&m_Transformation );
    LudoRenderer::GetInstance()->DrawVertices(*m_RailVertices,RAIL_NUM_VERTICES, m_RailIndices, RAIL_NUM_VERTICES, m_RailTexture);
    LudoRenderer::GetInstance()->GetDevice()->SetTransform( D3DTS_WORLD, &CurrentMatrix );

    GameObject::Render();
}

void Rail::SetNextRail(Rail *nextRail)
{
    m_NextRail = nextRail;
}

Rail *Rail::GetNextRail()
{
    return m_NextRail;
}

LudoVector *Rail::GetPosition() 
{ 
    return m_Position; 
}