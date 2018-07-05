#ifndef SIMPLE_DSO_LOADER
#define SIMPLE_DSO_LOADER

#include <stdlib.h>
#include <string.h>

/* gcc simple_dso_loader.c -c -Wall */
/*
linking:
 linux:
  -> -ldl
 windows:
  -> 

*/

/* OS DETECTOR */

#ifdef _WIN32
    //define something for Windows (32-bit and 64-bit, this part is common)
    #include <windows.h>
    #include <winbase.h>
    #include <windef.h>

    #ifdef _WIN64
        //define something for Windows (64-bit only)
    #else
        //define something for Windows (32-bit only)
    #endif

#elif __unix__ 
    // Unix
    #include <dlfcn.h> // DSO library

    #if __APPLE__
        // #error "No support for apple devices"
        #include "TargetConditionals.h"
        #if TARGET_IPHONE_SIMULATOR
            // iOS Simulator
        #elif TARGET_OS_IPHONE
            // iOS device
        #elif TARGET_OS_MAC
            // Other kinds of Mac OS
        #else
            #error "Unknown Apple platform"
        #endif
    #elif defined(__ANDROID__)
        // Android
        // #error "No support for android devices"
    #elif __linux__
         // linux

    #endif

#elif defined(_POSIX_VERSION)
    // POSIX
    #error "Supported?"
#else
    #error "Unknown compiler"
#endif


/* END OS DETECTOR */

typedef void* ALF_DSO_handl;
typedef void* ALF_DSO_func;


ALF_DSO_handl ALF_DSO_load_file(const char *file);
ALF_DSO_func ALF_DSO_load_function(ALF_DSO_handl handler, const char *function);
int ALF_DSO_close_file(ALF_DSO_handl handler);
char *ALF_DSO_get_last_error(void);


#endif /* SIMPLE_DSO_LOADER */