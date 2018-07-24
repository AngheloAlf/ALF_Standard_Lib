/** \file ALF_str_extra.h
* The ALF_std_extra library header.
* It includes the other headers.
**/

#ifndef ALF_std_extra_h
#define ALF_std_extra_h

#include "ALF_common.h"

#define ALF_std_extra_major_version 1
#define ALF_std_extra_minor_version 0
#define ALF_std_extra_patch_version 0
// #define ALF_std_extra_version ALF_std_extra_major_version.ALF_std_extra_minor_version
#define ALF_std_extra_version_str ALF_STR(ALF_std_extra_major_version)"."ALF_STR(ALF_std_extra_minor_version)"."ALF_STR(ALF_std_extra_patch_version)

#include "ALF_dso_loader.h"

#endif /* ALF_std_extra_h */

