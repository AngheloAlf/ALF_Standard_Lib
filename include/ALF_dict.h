#ifndef ALF_dict_h
#define ALF_dict_h

#include "ALF_common.h"

#define ALF_dict_major_version (1)
#define ALF_dict_minor_version (0)
#define ALF_dict_patch_version (0)
#define ALF_dict_version (ALF_dict_major_version.ALF_dict_minor_version)
#define ALF_dict_version_str (ALF_STR(ALF_dict_major_version)"."ALF_STR(ALF_dict_minor_version)"."ALF_STR(ALF_dict_patch_version))


#include "stdlib.h"
#include "string.h"

typedef struct alf_dict{
	struct alf_dict *next;
	char *key;
	void *value;
} ALF_Dict;

ALF_Dict *ALF_dict_init(void);
int ALF_dict_add(ALF_Dict *dict, const char *key, void *value);
void *ALF_dict_get(ALF_Dict *dict, const char *key);
int ALF_dict_delete(ALF_Dict *dict, const char *key);
int ALF_dict_length(ALF_Dict *dict);
void ALF_dict_free(ALF_Dict *dict);

#endif /* ALF_dict_h */
