/** \file ALF_dso_loader.h
* A simple cross-platform wraper to use Dynamic Shared objects.
**/

#ifndef ALF_dso_loader_h
#define ALF_dso_loader_h

#include "ALF_common.h"

#define ALF_dso_loader_major_version 1
#define ALF_dso_loader_minor_version 0
#define ALF_dso_loader_patch_version 0
#define ALF_dso_loader_version ALF_MAKE_VERSION(ALF_dso_loader_major_version, ALF_dso_loader_minor_version)
#define ALF_dso_loader_version_str ALF_STR(ALF_dso_loader_major_version)"."ALF_STR(ALF_dso_loader_minor_version)"."ALF_STR(ALF_dso_loader_patch_version)

typedef void* ALF_DSO_handl;
typedef void* ALF_DSO_func;

/// Loads a .dll or .so file.
/**
 * Params: 

 * -const char *file: the route and name of the file.

 * Return value:

 * ->ALF_DSO_handl: The dso handler. NULL in case of error.

**/
ALF_DSO_handl ALF_DSO_load_file(const char *file);
/// Search a function in the handler.
ALF_DSO_func ALF_DSO_load_function(ALF_DSO_handl handler, const char *function);
/// Closes the handler.
int ALF_DSO_close_file(ALF_DSO_handl handler);
/// Returns the last error.
char *ALF_DSO_get_error(void);


#endif /* ALF_dso_loader_h */