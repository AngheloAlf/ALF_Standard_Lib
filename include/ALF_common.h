#ifndef ALF_common_h
#define ALF_common_h

#define _ALF_STR(x) #x
#define ALF_STR(x) _ALF_STR(x)

#define ALF_common_major_version (1)
#define ALF_common_minor_version (0)
#define ALF_common_patch_version (0)
#define ALF_common_version (ALF_common_major_version.ALF_common_minor_version)
#define ALF_common_version_str (ALF_STR(ALF_common_major_version)"."ALF_STR(ALF_common_minor_version)"."ALF_STR(ALF_common_patch_version))



#endif /* ALF_common_h */
