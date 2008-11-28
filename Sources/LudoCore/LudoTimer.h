#pragma once
#include "LudoCore/Singleton.h"

class LudoTimer : public Singleton<LudoTimer>
{
    friend class Singleton<LudoTimer>;

public:
    void Update();
    UINT64 GetDeltaTime() const;

private:
    LudoTimer();
    ~LudoTimer();

    UINT64 GetTickCount64() const;

    UINT64 m_DeltaTime;

    // Tick Count
    UINT64 m_CurrFrameTick;
    UINT64 m_LastFrameTick;
};
