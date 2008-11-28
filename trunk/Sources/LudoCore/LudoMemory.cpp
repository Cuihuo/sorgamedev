///////////////////////////////
// Filename: LudoMemory.cpp
// Description: Internal memory manager
// Creation Date: 14/01/2008
///////////////////////////////
#include "LudoCore/LudoGlobal.h"
#include "LudoMemory.h"
#include "ErrorLogger.h"
using std::string;
using std::map;

// Overload of new and delete operators
#ifdef _DEBUG
void* __cdecl operator new(unsigned int size, const char *file, int line)
{
    return LudoMemory::GetInstance(false)->New(size, false, file, line);
}

void* __cdecl operator new[](unsigned int size, const char *file, int line)
{
    return LudoMemory::GetInstance(false)->New(size, true, file, line);
}

void __cdecl operator delete(void *address)
{
    LudoMemory::GetInstance(false)->Delete(address);
}

void __cdecl operator delete[](void *address)
{
    LudoMemory::GetInstance(false)->Delete(address);
}

void __cdecl operator delete(void* address, const char *file, int line)
{
    file;
    line;
    return LudoMemory::GetInstance()->Delete(address);
}

void __cdecl operator delete[](void* address, const char *file, int line)
{
    file;
    line;
    return LudoMemory::GetInstance()->Delete(address);
}

void __cdecl Delete(void *address)
{
    if (LudoMemory::GetExistingInstance())
    {
        return LudoMemory::GetInstance()->Delete(address);
    }
    else if (address)
    {
        free(address);
    }
}
#endif

LudoMemory::LudoMemory()
{
}

LudoMemory::~LudoMemory()
{
    if (m_AllocatedMemory.size() != 0)
    {
        ErrorLogger::GetInstance()->LogError(L"Memory Manager : Destructor call without all memory freed", false);
        PrintArray();
    }
}

void* LudoMemory::New(unsigned int size, bool isArray, string file, int line)
{
    if(size <= 0)
    {
        return 0;
    }

    void *mem = malloc(size);

    MemoryBlockInfo info;
    info.size = size;
    info.array = isArray;
    info.file = file;
    info.line = line;
    info.memAddr = mem;

    m_AllocatedMemory[(char*)mem] = info;

    return mem;
}

void LudoMemory::Delete(void *memory)
{
    if(memory == NULL || memory == this)
    {
        return;
    }

    map <char*, MemoryBlockInfo>::iterator iter = m_AllocatedMemory.find((char*)memory);
    if (iter != m_AllocatedMemory.end())
    {
        m_AllocatedMemory.erase(iter);
    }

    free(memory);
}

void LudoMemory::PrintArray()
{
    map <char*, MemoryBlockInfo>::iterator iter = m_AllocatedMemory.begin();
    while(iter != m_AllocatedMemory.end())
    {
        wchar_t error[DEFAULT_ERROR_STRING_LENGTH];
        swprintf_s(error,DEFAULT_ERROR_STRING_LENGTH, L"File: %S \nLine: %i \nSize: %i", ((*iter).second.file).c_str(),(*iter).second.line,(*iter).second.size);
        ErrorLogger::GetInstance(false)->LogError(error, false);
        iter++;
    }
}
