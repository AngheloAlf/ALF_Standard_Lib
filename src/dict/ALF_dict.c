#include "ALF_dict.h"

ALF_Dict *ALF_dict_init(){
	ALF_Dict *dict = malloc(sizeof(ALF_Dict *));
	dict->next = NULL;
	dict->value = NULL;
	dict->key = NULL;
	return dict;
}

int ALF_dict_add(ALF_Dict *dict, const char *key, void *value){
	ALF_Dict *aux = dict;
	for(; aux->next != NULL; aux = aux->next){
		if(strcmp(aux->key, key) == 0){
			aux->value = value;
			return 0;
		}
	}
	aux->next = ALF_dict_init();
	aux->value = value;
	aux->key = malloc(sizeof(char *) * (strlen(key) + 1));
	strcpy(aux->key, key);
	return 0;
}

void *ALF_dict_get(ALF_Dict *dict, const char *key){
	ALF_Dict *aux = dict;
	for(; aux != NULL && aux->key != NULL; aux = aux->next){
		if(strcmp(aux->key, key) == 0){
			return aux->value;
		}
	}
	return NULL;
}

int ALF_dict_delete(ALF_Dict *dict, const char *key){
    ALF_Dict *aux = dict, *aux2;
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

int ALF_dict_length(ALF_Dict *dict){
	ALF_Dict *aux = dict;
	int len = 0;
	for(; aux->next != NULL; aux = aux->next){
		len += 1;
	}

	return len;
}

void ALF_dict_free(ALF_Dict *dict){
    if(dict->next != NULL){
        ALF_dict_free(dict->next);
    }
    free(dict->key);
    free(dict);
	return;
}
