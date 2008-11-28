///////////////////////////////
// Filename: FileReader.cpp
// Description: Access to local files
///////////////////////////////
#include "LudoCore/LudoGlobal.h"
#include "FileReader.h"
#include "ErrorLogger.h"

using std::fstream;
using std::ios;

FileReader::FileReader(std::wstring fileName)
{
    m_FileName = fileName;
}

FileReader::~FileReader()
{
}

void* FileReader::GetFileData(int &size)
{
    fstream fin(m_FileName.c_str(), ios::in|ios::binary|ios::ate);
    char *memblock = 0;
    size = 0;
    if ( fin.is_open() )
    {
        size = (int)fin.tellg();

        memblock = LUDO_NEW char[(int)size + 1];
        memset(memblock, 0, (int)size + 1);

        fin.seekg (0, ios::beg);
        fin.read (memblock, size);
        fin.close();
    }
    else
    {
        wchar_t error[DEFAULT_ERROR_STRING_LENGTH];
        swprintf_s(error,sizeof(error), L"GetFileData() function called on an unvalid file : %s\n", m_FileName.c_str());
        ErrorLogger::GetInstance()->LogError(error, false);
    }

    return memblock;
}
