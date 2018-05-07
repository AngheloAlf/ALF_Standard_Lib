#include "simple_c_dict.h"

SimpleCDict *initSimpleCDict(){
	SimpleCDict *dict = malloc(sizeof(SimpleCDict *));
	dict->next = NULL;
	dict->value = NULL;
	dict->key = NULL;
	return dict;
}

int simpleCDict_add(SimpleCDict *dict, const char *key, void *value){
	SimpleCDict *aux = dict;
	for(; aux->next != NULL; aux = aux->next){
		if(strcmp(aux->key, key) == 0){
			aux->value = value;
			return 0;
		}
	}
	aux->next = initSimpleCDict();
	aux->value = value;
	aux->key = malloc(sizeof(char *) * (strlen(key) + 1));
	strcpy(aux->key, key);
	return 0;
}

void *simpleCDict_get(SimpleCDict *dict, const char *key){
	SimpleCDict *aux = dict;
	for(; aux != NULL && aux->key != NULL; aux = aux->next){
		if(strcmp(aux->key, key) == 0){
			return aux->value;
		}
	}
	return NULL;
}

int vsimpleCDict_delete(SimpleCDict *dict, const char *key){
    SimpleCDict *aux = dict, *aux2;
    if(aux->key != NULL && strcmp(aux->key, key) == 0){
        free(aux->key);
        aux->key = aux->next->key;
        aux->value = aux->next->value;
        aux2 = aux->next;
        if(aux->next != NULL){
            aux->next = aux->next->next;
        }
        else{
            aux->next = NULL;
        }
        free(aux2->next);
        return 0;
    }
    if(aux->next != NULL){
        for (; aux->next->next != NULL; aux = aux->next){
            if (strcmp(aux->next->key, key) == 0){
                free(aux->next->key);
                aux2 = aux->next->next;
                free(aux->next);
                aux->next = aux2;
                return 0;
            }
        }
    }
	return -2;
}

int simpleCDict_length(SimpleCDict *dict){
	SimpleCDict *aux = dict;
	int len = 0;
	for(; aux->next != NULL; aux = aux->next){
		len += 1;
	}

	return len;
}

void simpleCDict_free(SimpleCDict *dict){
    if(dict->next != NULL){
        simpleCDict_free(dict->next);
    }
    free(dict->key);
    free(dict);
	return;
}

/*
#include "stdio.h"

typedef int (*callback_type)(SimpleCDict* dict);

int main(){
	SimpleCDict *dict = initSimpleCDict();
	char test[] = "wea";
	char test2[] = "weaita";
	char test3[] = "weaota";
    printf("largo: %i\n", valueDict_length(dict));
	valueDict_add(dict, "wea", test);
	valueDict_add(dict, "wea2", (void *)valueDict_length);
	valueDict_add(dict, "wea3", test3);
    printf("largo: %i\n", valueDict_length(dict));
	printf("coso: %s\n", (char *)valueDict_get(dict, "wea"));
    // valueDict_delete(dict, "wea");
    // printf("largo: %i\n", valueDict_length(dict));
    int largo = ((callback_type)valueDict_get(dict, "wea2"))(dict);
    printf("largo: %i\n", largo);
    valueDict_free(dict);
	return 0;
}
*/

