#ifndef ALF_dso_loader_h
#define ALF_dso_loader_h

#include "ALF_common.h"

#define ALF_dso_loader_major_version (1)
#define ALF_dso_loader_minor_version (0)
#define ALF_dso_loader_patch_version (0)
#define ALF_dso_loader_version (ALF_dso_loader_major_version.ALF_dso_loader_minor_version)
#define ALF_dso_loader_version_str (ALF_STR(ALF_dso_loader_major_version)"."ALF_STR(ALF_dso_loader_minor_version)"."ALF_STR(ALF_dso_loader_patch_version))

#include <stdlib.h>
#include <string.h>

#ifdef __WIN32__
#   include <windows.h>
#else
#   include <dlfcn.h> // DSO library
#endif

typedef void* ALF_DSO_handl;
typedef void* ALF_DSO_func;


ALF_DSO_handl ALF_DSO_load_file(const char *file);
ALF_DSO_func ALF_DSO_load_function(ALF_DSO_handl handler, const char *function);
int ALF_DSO_close_file(ALF_DSO_handl handler);
char *ALF_DSO_get_last_error(void);


#endif /* ALF_dso_loader_h */