///////////////////////////////
// Filename: LudoTimer.cpp
///////////////////////////////
#include "LudoCore/LudoGlobal.h"
#include "LudoTimer.h"

static const int DELTA_CAP = 60;

LudoTimer::LudoTimer() :
m_DeltaTime(0)
{
    m_LastFrameTick = GetTickCount64();
}


LudoTimer::~LudoTimer()
{

}

void LudoTimer::Update()
{
    m_CurrFrameTick = GetTickCount();
    m_DeltaTime = (m_CurrFrameTick - m_LastFrameTick);
    m_LastFrameTick = m_CurrFrameTick;

    if (m_DeltaTime > DELTA_CAP)
    {
        m_DeltaTime = DELTA_CAP;
    }
}

UINT64 LudoTimer::GetTickCount64() const
{
    return GetTickCount();
}

UINT64 LudoTimer::GetDeltaTime() const
{
    return m_DeltaTime;
}

