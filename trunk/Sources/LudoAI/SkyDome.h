#pragma once
#include "GameObject.h"
#include "LudoRenderer/LudoRenderer.h"

class LudoVector;
class SkyDome : public GameObject
{
    static const int DELTA_THETA = 15;
    static const int DELTA_PHI = 15;
    static const int SKY_NUM_VERTICES = (int)((360/DELTA_THETA)*(90/DELTA_PHI)*4);

public:
    SkyDome(std::wstring baseName);
    virtual ~SkyDome();

    // Virtual
    void Init();
    // Virtual
    void Render();
    // Virtual
    void Update();

private:
    IDirect3DTexture9 *m_SkyTexture;
    CUSTOMVERTEX m_SkyVertices[SKY_NUM_VERTICES];
    int m_SkyIndices[SKY_NUM_VERTICES];
};
