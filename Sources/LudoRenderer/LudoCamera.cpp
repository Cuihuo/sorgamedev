///////////////////////////////
// Filename: LudoCamera.cpp
// Description: Camera Class
// Creation Date: 31/10/2007
///////////////////////////////
#include "LudoCore/LudoGlobal.h"
#include <math.h>
#include "LudoCamera.h"

static const float INIT_X = 0;
static const float INIT_Y = 0;
static const float INIT_Z = 1000;
static const float InitRotY = LUDO_PI;

LudoCamera::LudoCamera()
{
    Reset();
}

void LudoCamera::Reset()
{
    D3DXMatrixIdentity( &m_Matrix );
    Translate(INIT_X,INIT_Y,INIT_Z);
    RotateY(InitRotY);
}

void LudoCamera::Translate( float x, float y, float z )
{
    D3DXMATRIX    TransMat;
    D3DXMATRIX    ResultMat;

    D3DXMatrixMultiply( &ResultMat, &m_Matrix, D3DXMatrixTranslation( &TransMat, x, y, -z ) );

    m_Matrix = ResultMat;
}

void LudoCamera::RotateX( float Angle )
{
    D3DXMATRIX    RotMat;
    D3DXMATRIX    ResultMat;

    D3DXMatrixMultiply( &ResultMat, &m_Matrix, D3DXMatrixRotationX( &RotMat, Angle ) );

    m_Matrix = ResultMat;
}

void LudoCamera::RotateY( float Angle )
{
    D3DXMATRIX    RotMat;
    D3DXMATRIX    ResultMat;

    D3DXMatrixMultiply( &ResultMat, &m_Matrix, D3DXMatrixRotationY( &RotMat, Angle ) );

    m_Matrix = ResultMat;
}

void LudoCamera::RotateZ( float Angle )
{
    D3DXMATRIX    RotMat;
    D3DXMATRIX    ResultMat;

    D3DXMatrixMultiply( &ResultMat, &m_Matrix, D3DXMatrixRotationZ( &RotMat, Angle ) );

    m_Matrix = ResultMat;
}

D3DXMATRIX LudoCamera::GetMatrix()
{
    D3DXMATRIX    ResultMat;

    ResultMat = m_Matrix;

    return ResultMat;
}

void LudoCamera::SetMatrix(D3DXMATRIX matrix)
{
    m_Matrix = matrix;
}