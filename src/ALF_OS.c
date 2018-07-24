#include "ALF_OS.h"

#if defined(__unix__) || defined(__APPLE__) || defined(__MACH__)
#	include <unistd.h>
#endif

char ALF_isWindows(void){
	#ifdef _WIN32
	return 1;
	#else
	return 0;
	#endif
}
char ALF_isOSX(void){
	#if defined(__APPLE__)
	return 1;
	#else
	return 0;
	#endif
}
char ALF_isLinux(void){
	#ifdef __linux__
	return 1;
	#else
	return 0;
	#endif
}

char ALF_isWindows32(void){
	#if defined(_WIN32) && !defined(_WIN64)
	return 1;
	#else
	return 0;
	#endif
}
char ALF_isWindows64(void){
	#ifdef _WIN64
	return 1;
	#else
	return 0;
	#endif
}

char ALF_isUnix(void){
	#ifdef __unix__
	return 1;
	#else
	return 0;
	#endif
}
char ALF_isUnixOther(void){
	#ifdef __unix__
		#if !defined(__APPLE__) && !defined(__ANDROID__) && !defined(__linux__)
		return 1;
		#else
		return 0;
		#endif
	#else
	return 0;
	#endif
}

char ALF_isPosix(void){
	#ifdef _POSIX_VERSION
	return 1;
	#else
	return 0;
	#endif
}

char ALF_isAndroid(void){
	#if defined(__unix__) && defined(__ANDROID__)
	return 1;
	#else
	return 0;
	#endif
}

char ALF_isIOS(void){
	#if defined(__APPLE__) && TARGET_OS_IPHONE
	return 1;
	#else
	return 0;
	#endif
}
char ALF_isIOSSimulator(void){
	#if defined(__APPLE__) && TARGET_IPHONE_SIMULATOR
	return 1;
	#else
	return 0;
	#endif
}

char ALF_isOSXOther(void){
	#if defined(__APPLE__) && TARGET_OS_MAC
	return 1;
	#else
	return 0;
	#endif
}
char ALF_isAppleOther(void){
	#if defined(__APPLE__) && !TARGET_IPHONE_SIMULATOR && !TARGET_IPHONE_SIMULATOR && !TARGET_OS_MAC
	return 1;
	#else
	return 0;
	#endif
}

char ALF_isFreeBSD(void){
	#ifdef __FreeBSD__
	return 1;
	#else
	return 0;
	#endif
}

char ALF_isOther(void){
	#if !defined(_WIN32) && !defined(__APPLE__) && !defined(__unix__) && !defined(_POSIX_VERSION) && !defined(__FreeBSD__)
	return 1;
	#else
	return 0;
	#endif
}
