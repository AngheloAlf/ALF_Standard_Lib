#ifndef SIMPLE_C_DICT
#define SIMPLE_C_DICT

#include "stdlib.h"
#include "string.h"

typedef struct alf_dict{
	struct alf_dict *next;
	char *key;
	void *value;
} ALF_Dict;

ALF_Dict *ALF_dict_init();
int ALF_dict_add(ALF_Dict *dict, const char *key, void *value);
void *ALF_dict_get(ALF_Dict *dict, const char *key);
int ALF_dict_delete(ALF_Dict *dict, const char *key);
int ALF_dict_length(ALF_Dict *dict);
void ALF_dict_free(ALF_Dict *dict);

#endif /* SIMPLE_C_DICT */
