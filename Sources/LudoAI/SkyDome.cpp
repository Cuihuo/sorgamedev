///////////////////////////////
// Filename: SkyDome.cpp
///////////////////////////////
#include "LudoCore/LudoGlobal.h"
#include "SkyDome.h"
#include "LudoCore/LudoVector.h"
#include "LudoCore/LudoStringManager.h"

#include <math.h>

using std::vector;

static const float DTOR = LUDO_PI / 180.0f;
static const float RADIUS = 2000.0f;

SkyDome::SkyDome(std::wstring baseName) : GameObject(baseName)
{

}

SkyDome::~SkyDome()
{
    LUDO_SAFE_RELEASE(m_SkyTexture);
}

// Virtual
void SkyDome::Init()
{
    //Prepare texture and vertices
    D3DXIMAGE_INFO textureInfo;
    D3DXCreateTextureFromFileEx( LudoRenderer::GetInstance()->GetDevice(), LudoStringManager::GetInstance()->GetString(SKY_TEXTURE).c_str(), D3DX_DEFAULT, D3DX_DEFAULT, D3DX_DEFAULT, 0, 
        D3DFMT_A8R8G8B8, D3DPOOL_MANAGED, D3DX_DEFAULT, D3DX_DEFAULT, 0, &textureInfo, NULL, (IDirect3DTexture9**)&m_SkyTexture );

    int n = 0;
    for (int i = 0; i <= 90 - DELTA_PHI; i += DELTA_PHI)
    {
        float iDTor = i*DTOR;
        float iDPhiDTor = (i+DELTA_PHI)*DTOR;

        for (int j = 0; j <= 360 - DELTA_THETA; j += DELTA_THETA)
        {
            float jDTor = DTOR * j;
            float jDThetaDTor = DTOR*(j+DELTA_THETA);
            m_SkyVertices[n].x = RADIUS * sinf(iDTor) * cosf(jDTor);
            m_SkyVertices[n].y = RADIUS * cosf(iDTor) + GROUND_POS;
            m_SkyVertices[n].z = RADIUS * sinf(iDTor) * sinf(jDTor);
            n++;
            m_SkyVertices[n].x = RADIUS * sinf(iDPhiDTor) * cosf(jDTor);
            m_SkyVertices[n].y = RADIUS * cosf(iDPhiDTor) + GROUND_POS;
            m_SkyVertices[n].z = RADIUS * sinf(iDPhiDTor) * sinf(jDTor);
            n++;
            m_SkyVertices[n].x = RADIUS * sinf(iDTor) * cosf(jDThetaDTor);
            m_SkyVertices[n].y = RADIUS * cosf(iDTor) + GROUND_POS;
            m_SkyVertices[n].z = RADIUS * sinf(iDTor) * sinf(jDThetaDTor);
            n++;
            if (i > -90 && i < 90)
            {
                m_SkyVertices[n].x = RADIUS * sinf(iDPhiDTor) * cosf(jDThetaDTor);
                m_SkyVertices[n].y = RADIUS * cosf(iDPhiDTor) + GROUND_POS;
                m_SkyVertices[n].z = RADIUS * sinf(iDPhiDTor) * sinf(jDThetaDTor);
                n++;
            }
        }
    }

    // loop through the vertices
    for (int i=0;i<SKY_NUM_VERTICES;i++)
    {
        LudoVector vertexNormal = LudoVector(-m_SkyVertices[i].x,-m_SkyVertices[i].y,-m_SkyVertices[i].z);
        vertexNormal.Normalize();
        m_SkyVertices[i].nx = vertexNormal.GetX();
        m_SkyVertices[i].ny = vertexNormal.GetY();
        m_SkyVertices[i].nz = vertexNormal.GetZ();
        m_SkyVertices[i].u = asinf(m_SkyVertices[i].nx)/LUDO_PI + 0.5f;
        m_SkyVertices[i].v = asinf(m_SkyVertices[i].ny)/LUDO_PI + 0.5f;

        m_SkyIndices[i] = i;
    }

    for (int i = 0; i < SKY_NUM_VERTICES - 2; i++)
    {
        if (m_SkyVertices[i].u - m_SkyVertices[i+1].u > 0.9f)
        {
            m_SkyVertices[i+1].u += 1.0f;
        }
        if (m_SkyVertices[i+1].u - m_SkyVertices[i].u > 0.9f)
        {
            m_SkyVertices[i].u += 1.0f;
        }
        if (m_SkyVertices[i].u - m_SkyVertices[i+2].u > 0.9f)
        {
            m_SkyVertices[i+2].u += 1.0f;
        }
        if (m_SkyVertices[i+2].u - m_SkyVertices[i].u > 0.9f)
        {
            m_SkyVertices[i].u += 1.0f;
        }
        if (m_SkyVertices[i+1].u - m_SkyVertices[i+2].u  > 0.9f)
        {
            m_SkyVertices[i+2].u  += 1.0f;
        }
        if (m_SkyVertices[i+2].u  -m_SkyVertices[i+1].u > 0.9f)
        {
            m_SkyVertices[i+1].u += 1.0f;
        }
        if (m_SkyVertices[i].v - m_SkyVertices[i+1].v > 0.8f)
        {
            m_SkyVertices[i+1].v += 1.0f;
        }
        if (m_SkyVertices[i+1].v - m_SkyVertices[i].v > 0.8f)
        {
            m_SkyVertices[i].v += 1.0f;
        }
        if (m_SkyVertices[i].v - m_SkyVertices[i+2].v > 0.8f)
        {
            m_SkyVertices[i+2].v += 1.0f;
        }
        if (m_SkyVertices[i+2].v - m_SkyVertices[i].v > 0.8f)
        {
            m_SkyVertices[i].v += 1.0f;
        }
        if (m_SkyVertices[i+1].v - m_SkyVertices[i+2].v > 0.8f)
        {
            m_SkyVertices[i+2].v += 1.0f;
        }
        if (m_SkyVertices[i+2].v - m_SkyVertices[i+1].v > 0.8f)
        {
            m_SkyVertices[i+1].v += 1.0f;
        }
    }

    GameObject::Init();
}

// Virtual
void SkyDome::Render()
{
    // Render the skydome
//    LudoRenderer::GetInstance()->DrawVertices(*m_SkyVertices,SKY_NUM_VERTICES, m_SkyIndices, SKY_NUM_VERTICES, m_SkyTexture);
    LudoRenderer::GetInstance()->DrawVertices(*m_SkyVertices,SKY_NUM_VERTICES, NULL, 0, m_SkyTexture);


    GameObject::Render();
}

// Virtual
void SkyDome::Update()
{
    GameObject::Update();
}
