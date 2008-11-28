#pragma once

#include "LudoCore/LudoGlobal.h"
#include "Singleton.h"

static const int DEFAULT_ERROR_STRING_LENGTH = 255;

class ErrorLogger : public Singleton<ErrorLogger>
{
    friend class Singleton<ErrorLogger>;

public:
    void LogError(std::wstring error, bool critical);
    void Init(std::wstring filename, HWND mainWindowHandle);

private:
    ErrorLogger();
    ~ErrorLogger();

    FILE *m_ErrorLogFile;
    HWND m_MainWindow;
};
