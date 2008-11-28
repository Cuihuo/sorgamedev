#pragma once

#include "External/DirectXSDK/Include/d3dx9.h"

//--------------------------------------------------------------------------------------------------------------------------
class LudoCamera
{
protected:
    D3DXMATRIX        m_Matrix;

public:
    LudoCamera();

    void            Translate( float x, float y, float z );
    void            RotateX( float Angle );
    void            RotateY( float Angle );
    void            RotateZ( float Angle );
    void            Reset();

    D3DXMATRIX      GetMatrix();
    void            SetMatrix(D3DXMATRIX matrix);
};
