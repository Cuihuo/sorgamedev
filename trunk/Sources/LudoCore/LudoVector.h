#pragma once

class LudoVector
{
public:
    LudoVector();
    LudoVector(float x, float y, float z);
    LudoVector(const LudoVector &other);
    ~LudoVector();

    bool        operator==(const LudoVector &other) const;
    bool        operator!=(const LudoVector &other) const;
    LudoVector  operator+(const LudoVector &vectorToAdd) const;
    LudoVector  operator-(const LudoVector &vectorToSub) const;
    LudoVector  operator*(const float constant) const;
    LudoVector  operator/(const float constant) const;
    LudoVector& operator=(const LudoVector &vector);
    LudoVector  operator+=(const LudoVector &vectorToAdd);
    LudoVector  operator-=(const LudoVector &vectorToSubstract);
    LudoVector  operator*=(const LudoVector &vectorToMultiply);
    LudoVector  operator*=(const float constantToMultiply);

    void        Normalize();
    void        Add(const LudoVector &vectorToAdd);
    void        Subtract(const LudoVector &vectorToSubtract);
    void        Multiply(const LudoVector &vectorToMultiply);
    LudoVector  Cross(const LudoVector &vector) const;
    float       Dot(const LudoVector &vector) const;

    void SetX(float value);
    void SetY(float value);
    void SetZ(float value);
    void Set(float valueX, float valueY, float valueZ);

    float GetX() const;
    float GetY() const;
    float GetZ() const;
    float GetLength() const;

private:
    float m_X;
    float m_Y;
    float m_Z;
};
