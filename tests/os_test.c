#include "ALF_std.h"
#include "stdio.h"

int main(int argc, char *argv[]){
	printf("ALF_isWindows: %d\n", ALF_isWindows());
	printf("ALF_isOSX: %d\n", ALF_isOSX());
	printf("ALF_isMac: %d\n", ALF_isMac());
	printf("ALF_isLinux: %d\n", ALF_isLinux());
	printf("ALF_isWindows32: %d\n", ALF_isWindows32());
	printf("ALF_isWindows64: %d\n", ALF_isWindows64());
	printf("ALF_isUnix: %d\n", ALF_isUnix());
	printf("ALF_isUnixOther: %d\n", ALF_isUnixOther());
	printf("ALF_isPosix: %d\n", ALF_isPosix());
	printf("ALF_isAndroid: %d\n", ALF_isAndroid());
	printf("ALF_isIOS: %d\n", ALF_isIOS());
	printf("ALF_isIphone: %d\n", ALF_isIphone());
	printf("ALF_isIOSSimulator: %d\n", ALF_isIOSSimulator());
	printf("ALF_isIphoneSimulator: %d\n", ALF_isIphoneSimulator());
	printf("ALF_isOSXOther: %d\n", ALF_isOSXOther());
	printf("ALF_isMACOther: %d\n", ALF_isMACOther());
	printf("ALF_isAppleOther: %d\n", ALF_isAppleOther());
	printf("ALF_isFreeBSD: %d\n", ALF_isFreeBSD());
	printf("ALF_isOther: %d\n", ALF_isOther());

	ALF_raw_input("ENTER");

	return 0;
}
