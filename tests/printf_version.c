#include "ALF_std.h"
#include "ALF_std_extra.h"
#include <stdio.h>

int main(){
	printf("ALF_std_major_version: %d\n", ALF_std_major_version);
	printf("ALF_std_minor_version: %d\n", ALF_std_minor_version);
	printf("ALF_std_patch_version: %d\n", ALF_std_patch_version);
	printf("ALF_std_version: %f\n", ALF_std_version);
	printf("ALF_std_version_str: %s\n", ALF_std_version_str);

	printf("\n");

	printf("ALF_std_extra_major_version: %d\n", ALF_std_extra_major_version);
	printf("ALF_std_extra_minor_version: %d\n", ALF_std_extra_minor_version);
	printf("ALF_std_extra_patch_version: %d\n", ALF_std_extra_patch_version);
	printf("ALF_std_extra_version: %f\n", ALF_std_extra_version);
	printf("ALF_std_extra_version_str: %s\n", ALF_std_extra_version_str);

	printf("\n");

	// printf("%lf\n", 1e3);

	return 0;
}
