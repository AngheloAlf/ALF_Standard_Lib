#include "ALF_std/ALF_OS.h"

#if defined(__unix__) || defined(__APPLE__) || defined(__MACH__)
#    include <unistd.h>
#endif

bool ALF_OS_isWindows(void){
    #ifdef _WIN32
    return true;
    #else
    return false;
    #endif
}
bool ALF_OS_isOSX(void){
    #if defined(__APPLE__)
    return true;
    #else
    return false;
    #endif
}
bool ALF_OS_isLinux(void){
    #ifdef __linux__
    return true;
    #else
    return false;
    #endif
}

bool ALF_OS_isWindows32(void){
    #if defined(_WIN32) && !defined(_WIN64)
    return true;
    #else
    return false;
    #endif
}
bool ALF_OS_isWindows64(void){
    #ifdef _WIN64
    return true;
    #else
    return false;
    #endif
}

bool ALF_OS_isUnix(void){
    #ifdef __unix__
    return true;
    #else
    return false;
    #endif
}
bool ALF_OS_isUnixOther(void){
    #ifdef __unix__
        #if !defined(__APPLE__) && !defined(__ANDROID__) && !defined(__linux__)
        return true;
        #else
        return false;
        #endif
    #else
    return false;
    #endif
}

bool ALF_OS_isPosix(void){
    #ifdef _POSIX_VERSION
    return true;
    #else
    return false;
    #endif
}

bool ALF_OS_isAndroid(void){
    #if defined(__unix__) && defined(__ANDROID__)
    return true;
    #else
    return false;
    #endif
}

bool ALF_OS_isIOS(void){
    #if defined(__APPLE__) && TARGET_OS_IPHONE
    return true;
    #else
    return false;
    #endif
}
bool ALF_OS_isIOSSimulator(void){
    #if defined(__APPLE__) && TARGET_IPHONE_SIMULATOR
    return true;
    #else
    return false;
    #endif
}

bool ALF_OS_isOSXOther(void){
    #if defined(__APPLE__) && TARGET_OS_MAC
    return true;
    #else
    return false;
    #endif
}
bool ALF_OS_isAppleOther(void){
    #if defined(__APPLE__) && !TARGET_IPHONE_SIMULATOR && !TARGET_IPHONE_SIMULATOR && !TARGET_OS_MAC
    return true;
    #else
    return false;
    #endif
}

bool ALF_OS_isFreeBSD(void){
    #ifdef __FreeBSD__
    return true;
    #else
    return false;
    #endif
}

bool ALF_OS_isOther(void){
    #if !defined(_WIN32) && !defined(__APPLE__) && !defined(__unix__) && !defined(_POSIX_VERSION) && !defined(__FreeBSD__)
    return true;
    #else
    return false;
    #endif
}
