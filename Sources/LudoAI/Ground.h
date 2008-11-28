#pragma once
#include "GameObject.h"
#include "LudoRenderer/LudoRenderer.h"

class LudoVector;

class Ground : public GameObject
{
    static const int GROUND_NUM_VERTICES = 4; 
public:
    Ground(std::wstring baseName);
    virtual ~Ground();

    // Virtual
    void Init();
    // Virtual
    void Render();
    // Virtual
    void Update();

private:
    LudoVector *m_Position;

    IDirect3DTexture9 *m_GroundTexture;
    CUSTOMVERTEX m_GroundVertices[GROUND_NUM_VERTICES];

};
