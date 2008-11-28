//////////////////////////////
// Filename: LudoStringManager.cpp
// Description: String Manager Class (Singleton)
// Creation Date: 23/01/2008
//////////////////////////////
#include "LudoCore/LudoGlobal.h"
#include "LudoStringManager.h"

using std::wstring;
using std::map;

LudoStringManager::LudoStringManager()
{
    m_hModule = NULL;

#ifdef _DEBUG
    m_hModule = LoadLibrary(L"LudoResources_D.dll");
#else
    m_hModule = LoadLibrary(L"LudoResources.dll");
#endif
}

LudoStringManager::~LudoStringManager()
{
    if ( m_hModule )
    {
        FreeLibrary(m_hModule);
    }
}

wstring LudoStringManager::GetString(int stringId)
{
    wstring retStr = L"";

    if ( m_hModule == NULL )
    {
        return L"";
    }

    if ( m_StringMap.find(stringId) == m_StringMap.end() )
    {
        wchar_t buffer[MAX_STRING_LENGTH];
        memset(buffer, 0, sizeof(buffer));

        int result = LoadStringW(m_hModule, stringId, (LPWSTR)&buffer, MAX_STRING_LENGTH);

        if ( result == 0 )
        {
            return L"";
        }
        m_StringMap[stringId] = wstring(buffer);
    }
    retStr = m_StringMap[stringId];

    return retStr;
}
