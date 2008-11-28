///////////////////////////////
// Filename: LudoVector.cpp
///////////////////////////////
#include "LudoCore/LudoGlobal.h"
#include "LudoVector.h"
#include <cmath>

LudoVector::LudoVector()
{
    m_X = 0.0f;
    m_Y = 0.0f;
    m_Z = 0.0f;
}
LudoVector::LudoVector(float x, float y, float z)
{
    m_X = x;
    m_Y = y;
    m_Z = z;
}

LudoVector::~LudoVector()
{

}

LudoVector::LudoVector(const LudoVector &other)
{
    m_X = other.GetX();
    m_Y = other.GetY();
    m_Z = other.GetZ();
}

LudoVector & LudoVector::operator=(const LudoVector &vector)
{
    m_X = vector.GetX();
    m_Y = vector.GetY();
    m_Z = vector.GetZ();
    return *this;
}

void LudoVector::Normalize()
{
    float vectorLength = GetLength();
    m_X /= vectorLength;
    m_Y /= vectorLength;
    m_Z /= vectorLength;
}

void LudoVector::Add(const LudoVector &vectorToAdd)
{
    m_X += vectorToAdd.GetX();
    m_Y += vectorToAdd.GetY();
    m_Z += vectorToAdd.GetZ();
}

void LudoVector::Subtract(const LudoVector &vectorToSubtract)
{
    m_X -= vectorToSubtract.GetX();
    m_Y -= vectorToSubtract.GetY();
    m_Z -= vectorToSubtract.GetZ();
}

void LudoVector::Multiply(const LudoVector &vectorToMultiply)
{
    m_X *= vectorToMultiply.GetX();
    m_Y *= vectorToMultiply.GetY();
    m_Z *= vectorToMultiply.GetZ();
}

LudoVector LudoVector::operator+=(const LudoVector &vectorToAdd)
{
    Add(vectorToAdd);
    return *this;
}

LudoVector LudoVector::operator-=(const LudoVector &vectorToSubtract)
{
    Subtract(vectorToSubtract);
    return *this;
}

LudoVector LudoVector::operator*=(const LudoVector &vectorToMultiply)
{
    Multiply(vectorToMultiply);
    return *this;
}

LudoVector LudoVector::operator*=(const float constantToMultiply)
{
    m_X *= constantToMultiply;
    m_Y *= constantToMultiply;
    m_Z *= constantToMultiply;

    return *this;
}

LudoVector LudoVector::operator+(const LudoVector &vectorToAdd) const
{
    return LudoVector(m_X + vectorToAdd.GetX(), m_Y + vectorToAdd.GetY(), m_Z + vectorToAdd.GetZ());
}

LudoVector LudoVector::operator-(const LudoVector &vectorToSub) const
{
    return LudoVector(m_X - vectorToSub.GetX(), m_Y - vectorToSub.GetY(), m_Z - vectorToSub.GetZ());
}

LudoVector LudoVector::operator*(const float constant) const
{
    return LudoVector(m_X * constant, m_Y * constant, m_Z * constant);
}

LudoVector LudoVector::operator/(float constant) const
{
    return LudoVector(m_X / constant, m_Y / constant, m_Z / constant);
}

bool LudoVector::operator==(const LudoVector &other) const
{
    if (m_X != other.GetX() || m_Y != other.GetY() || m_Z != other.GetZ())
    {
        return false;
    }

    return true;
}

bool LudoVector::operator!=(const LudoVector &other) const
{
    if (m_X != other.GetX() || m_Y != other.GetY() || m_Z != other.GetZ())
    {
        return true;
    }

    return false;
}

LudoVector LudoVector::Cross(const LudoVector &vector) const
{
    LudoVector result(m_Y * vector.GetZ() - m_Z * vector.GetY(),
        -(m_X * vector.GetZ() - m_Z * vector.GetX()),
        m_X * vector.GetY() - m_Y * vector.GetX());

    return result;
}

float LudoVector::Dot(const LudoVector &vector) const
{
    return m_X * vector.GetX() + m_Y * vector.GetY() + m_Z * vector.GetZ();
}

float LudoVector::GetLength() const
{
    return sqrt(m_X * m_X + m_Y * m_Y + m_Z * m_Z);
}

void LudoVector::SetX(float value)
{
    m_X = value;
}

void LudoVector::SetY(float value)
{
    m_Y = value;
}

void LudoVector::SetZ(float value)
{
    m_Z = value;
}

void LudoVector::Set(float valueX, float valueY, float valueZ)
{
    m_X = valueX;
    m_Y = valueY;
    m_Z = valueZ;
}

float LudoVector::GetX() const
{
    return m_X;
}

float LudoVector::GetY() const
{
    return m_Y;
}

float LudoVector::GetZ() const
{
    return m_Z;
}
