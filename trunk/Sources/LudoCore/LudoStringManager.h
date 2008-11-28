#pragma once
#include "LudoCore/Singleton.h"
#include "LudoResources/resource.h"

class LudoStringManager : public Singleton<LudoStringManager>
{
    friend class Singleton<LudoStringManager>;

public:
    std::wstring GetString(int stringId);

private:
    const static int MAX_STRING_LENGTH = 512;

    LudoStringManager();
    ~LudoStringManager();

    HMODULE m_hModule;

    std::map<int, std::wstring> m_StringMap;
};
