#pragma once
#include <map>
#include "Singleton.h"

#ifdef _DEBUG
extern void* operator new(unsigned int size, const char* file, int line);
extern void* operator new[](unsigned int size, const char* file, int line);
extern void operator delete(void* address, const char* file, int line);
extern void operator delete[](void* address, const char* file, int line);
extern void Delete(void* address);

#define LUDO_NEW new(__FILE__, __LINE__)
#define LUDO_DELETE delete

#endif

class LudoMemory : public Singleton<LudoMemory>
{
    friend class Singleton<LudoMemory>;

public:
    void* New(unsigned int size, bool isArray, std::string file, int line);
    void Delete(void* memory);
    void PrintArray();

private:
    struct MemoryBlockInfo
    {
        void *memAddr;
        unsigned int size;
        bool array;
        std::string file;
        int line;
    };

    LudoMemory();
    ~LudoMemory();

    std::map<char*, MemoryBlockInfo> m_AllocatedMemory;
};
