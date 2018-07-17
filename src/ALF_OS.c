#include "ALF_OS.h"

char ALF_isWindows(void){
	#ifdef __WIN32__
	return 1;
	#else
	return 0;
	#endif
}
char ALF_isOSX(void){
	#if __APPLE__
	return 1;
	#else
	return 0;
	#endif
}
char ALF_isLinux(void){
	#if __linux__
	return 1;
	#else
	return 0;
	#endif
}

char ALF_isWindows32(void){
	#if defined(__WIN32__) && !defined(__WIN64__)
	return 1;
	#else
	return 0;
	#endif
}
char ALF_isWindows64(void){
	#ifdef __WIN64__
	return 1;
	#else
	return 0;
	#endif
}

char ALF_isUnix(void){
	#if __unix__
	return 1;
	#else
	return 0;
	#endif
}
char ALF_isUnixOther(void){
	#if __unix__
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
	#if __unix__ &&  defined(__ANDROID__)
	return 1;
	#else
	return 0;
	#endif
}

char ALF_isIOS(void){
	#if __APPLE__ && TARGET_OS_IPHONE
	return 1;
	#else
	return 0;
	#endif
}
char ALF_isIOSSimulator(void){
	#if __APPLE__ && TARGET_IPHONE_SIMULATOR
	return 1;
	#else
	return 0;
	#endif
}

char ALF_isOSXOther(void){
	#if __APPLE__ && TARGET_OS_MAC
	return 1;
	#else
	return 0;
	#endif
}
char ALF_isAppleOther(void){
	#if __APPLE__ && !TARGET_IPHONE_SIMULATOR && !TARGET_IPHONE_SIMULATOR && !TARGET_OS_MAC
	return 1;
	#else
	return 0;
	#endif
}


char ALF_isOther(void){
	#if !defined(__WIN32__) && !defined(__unix__) && !defined(_POSIX_VERSION)
	return 1;
	#else
	return 0;
	#endif
}