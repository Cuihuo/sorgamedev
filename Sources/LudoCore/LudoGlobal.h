#pragma once

// Modify the following defines if you have to target a platform prior to the ones specified below.
// Refer to MSDN for the latest info on corresponding values for different platforms.
#ifndef WINVER				// Allow use of features specific to Windows XP or later.
#define WINVER 0x0501		// Change this to the appropriate value to target other versions of Windows.
#endif

#ifndef _WIN32_WINNT		// Allow use of features specific to Windows XP or later.                   
#define _WIN32_WINNT 0x0501	// Change this to the appropriate value to target other versions of Windows.
#endif						

#ifndef _WIN32_WINDOWS		// Allow use of features specific to Windows 98 or later.
#define _WIN32_WINDOWS 0x0410 // Change this to the appropriate value to target Windows Me or later.
#endif

#ifndef _WIN32_IE			// Allow use of features specific to IE 6.0 or later.
#define _WIN32_IE 0x0600	// Change this to the appropriate value to target other versions of IE.
#endif

#define WIN32_LEAN_AND_MEAN		// Exclude rarely-used stuff from Windows headers

#include <Windows.h>

// C RunTime Header Files
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>

#include <string>
#include <vector>
#include <fstream>
#include <map>
#include <iostream>
#include <stdio.h>


#ifdef _DEBUG
extern void* operator new(unsigned int size, const char* file, int line);
extern void* operator new[](unsigned int size, const char* file, int line);
extern void operator delete(void* address, const char* file, int line);
extern void operator delete[](void* address, const char* file, int line);
extern void Delete(void* address);
#define LUDO_NEW new(__FILE__, __LINE__)
#else
#define LUDO_NEW new
#endif

#define LUDO_DELETE delete
#define LUDO_DELETE_ARRAY delete[]
#define LUDO_SAFE_DELETE(a) if( (a) != NULL ) { LUDO_DELETE (a); (a) = NULL ;}
#define LUDO_SAFE_DELETE_ARRAY(a) if( (a) != NULL ) { LUDO_DELETE_ARRAY (a); (a) = NULL ;}
#define LUDO_SAFE_RELEASE(a) if(a){a->Release(); a = NULL; }

static const float LUDO_2_PI = 2.0f * 3.141592653589793f;
static const float LUDO_PI = 3.141592653589793f;
static const float LUDO_PI_2 = 1.5707963267948965f;
static const float GROUND_POS = -420.0f;
