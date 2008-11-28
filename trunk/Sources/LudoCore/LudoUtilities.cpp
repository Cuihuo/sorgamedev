///////////////////////////////
// Filename: LudoUtilities.cpp
// Description: useful functions
///////////////////////////////
#include "LudoCore/LudoGlobal.h"
#include "LudoUtilities.h"
#include "ErrorLogger.h"
#include "LudoCore/LudoVector.h"
#include <sstream>

using std::wistringstream;
using std::ostringstream;
using std::wstring;

// static
int LudoUtilities::StringToInt(wstring s, int minValue, int maxValue, int defaultValue)
{
    wistringstream iss;
    iss.str(s);
    int i = 0;
    iss >> i;

    if (minValue != maxValue)
    {
        if (i < minValue || i > maxValue)
        {
            ErrorLogger::GetInstance()->LogError(L"Error converting a string to Int, outside of the specified range!", false);
            i = defaultValue;
        }
    }

    return i;
}

// static
bool LudoUtilities::AreStringsEqual(const wchar_t *s1, const wchar_t *s2, bool ignoreCase)
{
    if (ignoreCase)
    {
        return (wcscmp(s1, s2) == 0);
    }
    else
    {
        return (_wcsicmp(s1, s2) == 0);
    }
}

