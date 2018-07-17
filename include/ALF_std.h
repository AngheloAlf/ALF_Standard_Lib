#ifndef ALF_std_h
#define ALF_std_h

#include "ALF_common.h"

#define ALF_std_major_version (1)
#define ALF_std_minor_version (0)
#define ALF_std_patch_version (0)
#define ALF_std_version (ALF_std_major_version.ALF_std_minor_version)
#define ALF_std_version_str (ALF_STR(ALF_std_major_version)"."ALF_STR(ALF_std_minor_version)"."ALF_STR(ALF_std_patch_version))


#include "ALF_bool.h"
#include "ALF_dict.h"
#include "ALF_IO.h"
#include "ALF_jit.h"
#include "ALF_str.h"

#endif /* ALF_std_h */
