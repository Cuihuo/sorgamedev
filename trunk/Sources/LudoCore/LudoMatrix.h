#pragma once

#include <math.h>

class LudoMatrix
{
public:
    union
    {
        struct
        {
            float    _11;
            float    _12;
            float    _13;
            float    _14;
            float    _21;
            float    _22;
            float    _23;
            float    _24;
            float    _31;
            float    _32;
            float    _33;
            float    _34;
            float    _41;
            float    _42;
            float    _43;
            float    _44;
        };

        struct
        {
            float    m_Matrix[4][4];
        };
    };

    /////////////////////////////////////////////////////////////////////////////////////////
    // Constructor
    /////////////////////////////////////////////////////////////////////////////////////////
    inline LudoMatrix()
    {
        _11 = _12 = _13 = _14 = 0.0f;
        _21 = _22 = _23 = _24 = 0.0f;
        _31 = _32 = _33 = _34 = 0.0f;
        _41 = _42 = _43 = _44 = 0.0f;
    }

    inline LudoMatrix(    float _11, float _12, float _13, float _14,
        float _21, float _22, float _23, float _24,
        float _31, float _32, float _33, float _34,
        float _41, float _42, float _43, float _44 )
    {
        this->_11 = _11, this->_12 = _12, this->_13 = _13, this->_14 = _14;
        this->_21 = _21, this->_22 = _22, this->_23 = _23, this->_24 = _24;
        this->_31 = _31, this->_32 = _32, this->_33 = _33, this->_34 = _34;
        this->_41 = _41, this->_42 = _42, this->_43 = _43, this->_44 = _44;
    }

    /////////////////////////////////////////////////////////////////////////////////////////
    // Operateur
    /////////////////////////////////////////////////////////////////////////////////////////
    inline LudoMatrix operator * ( LudoMatrix& matrix )
    {
        LudoMatrix    result;

        result._11 = _11 * matrix._11 + _12 * matrix._21 + _13 * matrix._31 + _14 * matrix._41;
        result._12 = _11 * matrix._12 + _12 * matrix._22 + _13 * matrix._32 + _14 * matrix._42;
        result._13 = _11 * matrix._13 + _12 * matrix._23 + _13 * matrix._33 + _14 * matrix._43;
        result._14 = _11 * matrix._14 + _12 * matrix._24 + _13 * matrix._34 + _14 * matrix._44;

        result._21 = _21 * matrix._11 + _22 * matrix._21 + _23 * matrix._31 + _24 * matrix._41;
        result._22 = _21 * matrix._12 + _22 * matrix._22 + _23 * matrix._32 + _24 * matrix._42;
        result._23 = _21 * matrix._13 + _22 * matrix._23 + _23 * matrix._33 + _24 * matrix._43;
        result._24 = _21 * matrix._14 + _22 * matrix._24 + _23 * matrix._34 + _24 * matrix._44;

        result._31 = _31 * matrix._11 + _32 * matrix._21 + _33 * matrix._31 + _34 * matrix._41;
        result._32 = _31 * matrix._12 + _32 * matrix._22 + _33 * matrix._32 + _34 * matrix._42;
        result._33 = _31 * matrix._13 + _32 * matrix._23 + _33 * matrix._33 + _34 * matrix._43;
        result._34 = _31 * matrix._14 + _32 * matrix._24 + _33 * matrix._34 + _34 * matrix._44;

        result._41 = _41 * matrix._11 + _42 * matrix._21 + _43 * matrix._31 + _44 * matrix._41;
        result._42 = _41 * matrix._12 + _42 * matrix._22 + _43 * matrix._32 + _44 * matrix._42;
        result._43 = _41 * matrix._13 + _42 * matrix._23 + _43 * matrix._33 + _44 * matrix._43;
        result._44 = _41 * matrix._14 + _42 * matrix._24 + _43 * matrix._34 + _44 * matrix._44;

        return result;
    }

    inline void operator *= ( LudoMatrix& matrix )
    {
        LudoMatrix    result;

        result._11 = _11 * matrix._11 + _12 * matrix._21 + _13 * matrix._31 + _14 * matrix._41;
        result._12 = _11 * matrix._12 + _12 * matrix._22 + _13 * matrix._32 + _14 * matrix._42;
        result._13 = _11 * matrix._13 + _12 * matrix._23 + _13 * matrix._33 + _14 * matrix._43;
        result._14 = _11 * matrix._14 + _12 * matrix._24 + _13 * matrix._34 + _14 * matrix._44;

        result._21 = _21 * matrix._11 + _22 * matrix._21 + _23 * matrix._31 + _24 * matrix._41;
        result._22 = _21 * matrix._12 + _22 * matrix._22 + _23 * matrix._32 + _24 * matrix._42;
        result._23 = _21 * matrix._13 + _22 * matrix._23 + _23 * matrix._33 + _24 * matrix._43;
        result._24 = _21 * matrix._14 + _22 * matrix._24 + _23 * matrix._34 + _24 * matrix._44;

        result._31 = _31 * matrix._11 + _32 * matrix._21 + _33 * matrix._31 + _34 * matrix._41;
        result._32 = _31 * matrix._12 + _32 * matrix._22 + _33 * matrix._32 + _34 * matrix._42;
        result._33 = _31 * matrix._13 + _32 * matrix._23 + _33 * matrix._33 + _34 * matrix._43;
        result._34 = _31 * matrix._14 + _32 * matrix._24 + _33 * matrix._34 + _34 * matrix._44;

        result._41 = _41 * matrix._11 + _42 * matrix._21 + _43 * matrix._31 + _44 * matrix._41;
        result._42 = _41 * matrix._12 + _42 * matrix._22 + _43 * matrix._32 + _44 * matrix._42;
        result._43 = _41 * matrix._13 + _42 * matrix._23 + _43 * matrix._33 + _44 * matrix._43;
        result._44 = _41 * matrix._14 + _42 * matrix._24 + _43 * matrix._34 + _44 * matrix._44;

        *this = result;
    }

    bool operator == ( LudoMatrix& matrix )
    {
        return( memcmp( &matrix, this, sizeof( LudoMatrix ) ) == 0 );
    }

    bool operator != ( LudoMatrix& matrix )
    {
        return( memcmp( &matrix, this, sizeof( LudoMatrix ) ) != 0 );
    }

    /////////////////////////////////////////////////////////////////////////////////////////
    // Fonctions matricielles
    /////////////////////////////////////////////////////////////////////////////////////////
    inline void LoadIdentity()
    {
        _11 = _22 = _33 = _44 = 1.0f;
        _12 = _13 = _14 = 0.0f;
        _21 = _23 = _24 = 0.0f;
        _31 = _32 = _34 = 0.0f;
        _41 = _42 = _43 = 0.0f;
    }

    //------------------------------
    // From Game Programming Gems
    //------------------------------
    inline float det2x2( float a, float b, float c, float d )
    {
        return a*d - b*c;
    }

    inline float det3x3( float a1, float a2, float a3, float b1, float b2, float b3, float c1, float c2, float c3 )
    {
        return     a1 * det2x2(b2, b3, c2, c3)    - b1 * det2x2(a2, a3, c2, c3) + c1 * det2x2(a2, a3, b2, b3);
    }

    float Determinant ( const LudoMatrix& m )
    {
        float a1 = m._11;    float a2 = m._21;    float a3 = m._31;    float a4 = m._41;
        float b1 = m._12;    float b2 = m._22;    float b3 = m._32;    float b4 = m._42;
        float c1 = m._13;    float c2 = m._23;    float c3 = m._33;    float c4 = m._43;
        float d1 = m._14;    float d2 = m._24;    float d3 = m._34;    float d4 = m._44;

        return     a1 * det3x3(b2, b3, b4, c2, c3, c4, d2, d3, d4)
            -     b1 * det3x3(a2, a3, a4, c2, c3, c4, d2, d3, d4)
            +    c1 * det3x3(a2, a3, a4, b2, b3, b4, d2, d3, d4)
            -    d1 * det3x3(a2, a3, a4, b2, b3, b4, c2, c3, c4);
    }

    LudoMatrix Adjoint( const LudoMatrix& m )
    {
        float a1 = m._11;    float a2 = m._12;    float a3 = m._13;    float a4 = m._14;
        float b1 = m._21;    float b2 = m._22;    float b3 = m._23;    float b4 = m._24;
        float c1 = m._31;    float c2 = m._32;    float c3 = m._33;    float c4 = m._34;
        float d1 = m._41;    float d2 = m._42;    float d3 = m._43;    float d4 = m._44;

        // Adjoint(x,y) = -1^(x+y) * a(y,x)
        // Where a(i,j) is the 3x3 determinant of m with row i and col j removed
        LudoMatrix retVal;
        retVal._11 = det3x3(b2, b3, b4, c2, c3, c4, d2, d3, d4);
        retVal._12 = -det3x3(a2, a3, a4, c2, c3, c4, d2, d3, d4);
        retVal._13 = det3x3(a2, a3, a4, b2, b3, b4, d2, d3, d4);
        retVal._14 = -det3x3(a2, a3, a4, b2, b3, b4, c2, c3, c4);

        retVal._21 = -det3x3(b1, b3, b4, c1, c3, c4, d1, d3, d4);
        retVal._22 = det3x3(a1, a3, a4, c1, c3, c4, d1, d3, d4);
        retVal._23 = -det3x3(a1, a3, a4, b1, b3, b4, d1, d3, d4);
        retVal._24 = det3x3(a1, a3, a4, b1, b3, b4, c1, c3, c4);

        retVal._31 = det3x3(b1, b2, b4, c1, c2, c4, d1, d2, d4);
        retVal._32 = -det3x3(a1, a2, a4, c1, c2, c4, d1, d2, d4);
        retVal._33 = det3x3(a1, a2, a4, b1, b2, b4, d1, d2, d4);
        retVal._34 = -det3x3(a1, a2, a4, b1, b2, b4, c1, c2, c4);

        retVal._41 = -det3x3(b1, b2, b3, c1, c2, c3, d1, d2, d3);
        retVal._42 = det3x3(a1, a2, a3, c1, c2, c3, d1, d2, d3);
        retVal._43 = -det3x3(a1, a2, a3, b1, b2, b3, d1, d2, d3);
        retVal._44 = det3x3(a1, a2, a3, b1, b2, b3, c1, c2, c3);

        return retVal;
    }

    inline void Inverse()
    {
        float det = Determinant( *this );

        *this = Adjoint( *this );

        for( int i = 0; i < 4; ++i )
        {
            for( int j = 0; j < 4; ++j )
            {
                m_Matrix[i][j] /= det;
            }
        }
    }

    inline void Transpose()
    {
        float x;

        x = _21;
        _21    = _12;
        _12 = x;

        x = _31;
        _31 = _13;
        _13 = x;

        x = _41;
        _41 = _14;
        _14 = x;

        x = _32;
        _32 = _23;
        _23 = x;

        x = _42;
        _42 = _24;
        _24 = x;

        x = _43;
        _43 = _34;
        _34 = x;
    }

    /////////////////////////////////////////////////////////////////////////////////////////
    // Fonctions transformation
    /////////////////////////////////////////////////////////////////////////////////////////
    inline void RotX( float Angle )
    {
        float        cosine;
        float        sine;

        cosine    = (float)cos( Angle );
        sine    = (float)sin( Angle );

        LudoMatrix Mat;
        Mat.LoadIdentity();
        Mat._22    = cosine;
        Mat._23    = sine;
        Mat._32    = -sine;
        Mat._33    = cosine;

        *this *= Mat;
    }

    inline void RotY( float Angle )
    {
        float        cosine;
        float        sine;

        cosine    = (float)cos( Angle );
        sine    = (float)sin( Angle );

        LudoMatrix        Mat;
        Mat.LoadIdentity();
        Mat._11    = cosine;
        Mat._13    = sine;
        Mat._31    = -sine;
        Mat._33    = cosine;

        *this *= Mat;
    }

    inline void RotZ( float Angle )
    {
        float        cosine;
        float        sine;

        cosine    = (float)cos( Angle );
        sine    = (float)sin( Angle );

        LudoMatrix        Mat;
        Mat.LoadIdentity();
        Mat._11    = cosine;
        Mat._12    = -sine;
        Mat._21    = sine;
        Mat._22    = cosine;

        *this *= Mat;
    }

    inline void Trans( float x, float y, float z )
    {
        _41 += x;
        _42 += y;
        _43 += z;
    }

    inline void Scale( float x, float y, float z )
    {
        LudoMatrix        Mat;
        Mat.LoadIdentity();
        Mat._11    = x;
        Mat._22    = y;
        Mat._33    = z;

        *this *= Mat;
    }
};
