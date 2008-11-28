///////////////////////////////
// Filename: ErrorLogger.cpp
// Description: Error logger
///////////////////////////////
#include "LudoCore/LudoGlobal.h"
#include "ErrorLogger.h"

using std::wstring;
using std::ofstream;
using std::endl;

ErrorLogger::ErrorLogger()
{
    m_MainWindow = NULL;
    m_ErrorLogFile = NULL;
}

ErrorLogger::~ErrorLogger()
{
    fclose(m_ErrorLogFile);
}

void ErrorLogger::Init(std::wstring filename, HWND mainWindowHandle)
{
    m_MainWindow = mainWindowHandle;

    if (m_ErrorLogFile != NULL)
    {
        fclose(m_ErrorLogFile);
        m_ErrorLogFile = NULL;
    }

    _wfopen_s(&m_ErrorLogFile, filename.c_str(), L"w");
}


void ErrorLogger::LogError(std::wstring error, bool critical)
{
    if ( m_ErrorLogFile == NULL )
    {
        OutputDebugString(L"\nAn error occurred and the ErrorLog was not properly initialized.\n");
        OutputDebugString(error.c_str());
        DebugBreak();
        return;
    }

    fwprintf_s(m_ErrorLogFile, L"Error: %s\n", error.c_str());
    MessageBox(NULL, error.c_str(), L"Error thrown", MB_OK );
    
    if (critical)
    {
        exit(-1);
    }
}

