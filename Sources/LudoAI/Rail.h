#pragma once
#include "LudoCore/LudoMatrix.h"
#include "GameObject.h"
#include "LudoRenderer/LudoRenderer.h"

class LudoVector;

class Rail : public GameObject
{
    const static int RAIL_DEFINITION = 15;
    const static int RAIL_NUM_VERTICES = RAIL_DEFINITION * 2;

public:
    Rail(LudoVector* position, std::wstring baseName);
    virtual ~Rail();

    // Virtual
    void Init();
    // Virtual
    void Render();
    // Virtual
    void Update();

    void SetNextRail(Rail *nextRail);
    Rail *GetNextRail();
    LudoVector *GetPosition();

private:
    LudoVector *m_Position;
    Rail *m_NextRail;
    LudoMatrix m_Transformation;

    IDirect3DTexture9 *m_RailTexture;
    CUSTOMVERTEX m_RailVertices[RAIL_NUM_VERTICES];
    int m_RailIndices[RAIL_NUM_VERTICES];
};
