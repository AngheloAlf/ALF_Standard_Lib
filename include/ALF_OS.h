#ifndef ALF_OS_h
#define ALF_OS_h

#define ALF_OS_major_version (1)
#define ALF_OS_minor_version (0)
#define ALF_OS_patch_version (0)
#define ALF_OS_version (ALF_OS_major_version.ALF_OS_minor_version)
#define ALF_OS_version_str (ALF_STR(ALF_OS_major_version)"."ALF_STR(ALF_OS_minor_version)"."ALF_STR(ALF_OS_patch_version))


char ALF_isWindows(void);
char ALF_isOSX(void);
#define ALF_isMac() ALF_isOSX()
char ALF_isLinux(void);

char ALF_isWindows32(void);
char ALF_isWindows64(void);

char ALF_isUnix(void);
char ALF_isUnixOther(void);

char ALF_isPosix(void);

char ALF_isAndroid(void);

char ALF_isIOS(void);
#define ALF_isIphone() ALF_isIOS()
char ALF_isIOSSimulator(void);
#define ALF_isIphoneSimulator() ALF_isIOSSimulator()
char ALF_isOSXOther(void);
#define ALF_isMACOther() ALF_isOSXOther()
char ALF_isAppleOther(void);

char ALF_isFreeBSD(void);

char ALF_isOther(void);

/* OS DETECTOR */
/*
#ifdef __WIN32__
    //define something for Windows (32-bit and 64-bit, this part is common)
    #include <windows.h>
    // #include <winbase.h>
    // #include <windef.h>

    #ifdef __WIN64__
        //define something for Windows (64-bit only)
    #else
        //define something for Windows (32-bit only)
    #endif

#elif __unix__ 
    // Unix

    #if __APPLE__
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
    #elif __linux__
         // linux

    #include <unistd.h>
    #elif defined(_POSIX_VERSION)
        // POSIX
        #error "Supported?"

    #endif
#else
    #error "Unknown compiler"
#endif
*/

#endif /* ALF_OS_h */
