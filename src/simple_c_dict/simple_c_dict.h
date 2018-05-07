#ifndef SIMPLE_C_DICT
#define SIMPLE_C_DICT

#include "stdlib.h"
#include "string.h"

typedef struct simple_c_dict{
	struct simple_c_dict *next;
	char *key;
	void *value;
} SimpleCDict;

SimpleCDict *initSimpleCDict();
int simpleCDict_add(SimpleCDict *dict, const char *key, void *value);
void *simpleCDict_get(SimpleCDict *dict, const char *key);
int simpleCDict_delete(SimpleCDict *dict, const char *key);
int simpleCDict_length(SimpleCDict *dict);
void simpleCDict_free(SimpleCDict *dict);

#endif /* SIMPLE_C_DICT */