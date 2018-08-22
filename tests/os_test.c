#include "ALF_std.h"
#include "stdio.h"

int main(int argc, char *argv[]){
	printf("ALF_OS_isWindows: %d\n", ALF_OS_isWindows());
	printf("ALF_OS_isOSX: %d\n", ALF_OS_isOSX());
	printf("ALF_OS_isMac: %d\n", ALF_OS_isMac());
	printf("ALF_OS_isLinux: %d\n", ALF_OS_isLinux());
	printf("ALF_OS_isWindows32: %d\n", ALF_OS_isWindows32());
	printf("ALF_OS_isWindows64: %d\n", ALF_OS_isWindows64());
	printf("ALF_OS_isUnix: %d\n", ALF_OS_isUnix());
	printf("ALF_OS_isUnixOther: %d\n", ALF_OS_isUnixOther());
	printf("ALF_OS_isPosix: %d\n", ALF_OS_isPosix());
	printf("ALF_OS_isAndroid: %d\n", ALF_OS_isAndroid());
	printf("ALF_OS_isIOS: %d\n", ALF_OS_isIOS());
	printf("ALF_OS_isIphone: %d\n", ALF_OS_isIphone());
	printf("ALF_OS_isIOSSimulator: %d\n", ALF_OS_isIOSSimulator());
	printf("ALF_OS_isIphoneSimulator: %d\n", ALF_OS_isIphoneSimulator());
	printf("ALF_OS_isOSXOther: %d\n", ALF_OS_isOSXOther());
	printf("ALF_OS_isMACOther: %d\n", ALF_OS_isMACOther());
	printf("ALF_OS_isAppleOther: %d\n", ALF_OS_isAppleOther());
	printf("ALF_OS_isFreeBSD: %d\n", ALF_OS_isFreeBSD());
	printf("ALF_OS_isOther: %d\n", ALF_OS_isOther());

	ALF_IO_raw_input("ENTER");

	return 0;
}
