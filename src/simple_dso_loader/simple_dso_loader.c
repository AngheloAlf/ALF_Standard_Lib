#include "simple_dso_loader.h"

S_DSO_handl S_DSO_load_file(const char *file){
	S_DSO_handl handler = NULL;
	#ifdef _WIN32
		handler = (S_DSO_handl)LoadLibrary(file);
	#elif __unix__
		handler = (S_DSO_handl)dlopen(file, RTLD_LAZY);
	#endif
	return handler;
}

S_DSO_func S_DSO_load_function(S_DSO_handl handler, const char *function){
	S_DSO_func func = NULL;
	#ifdef _WIN32
		func = (S_DSO_handl)GetProcAddress((HMODULE)handler, function);
	#elif __unix__
		func = (S_DSO_handl)dlsym(file, function);
	#endif
	return func;
}

int S_DSO_close_file(S_DSO_handl handler){
	int retVal = 0;
	#ifdef _WIN32
		retVal = !FreeLibrary((HMODULE)handler); // Returns nonzero in success
	#elif __unix__
		retVal = dlclose(handler);
	#endif
	return retVal;
}

char *S_DSO_get_last_error(void){
	char *result = NULL;
	char *aux = NULL;

	#ifdef _WIN32
		result = malloc(sizeof(char) * 32);
		sprintf(result, "%lu", GetLastError());
	#elif __linux__
		aux = dlerror();
	#elif __unix__
		aux = dlerror();
	#endif

	if(result == NULL && aux != NULL){
		result = malloc(sizeof(char) * (strlen(aux) + 1));
		strcpy(result, aux);
	}

	return result;
}

/*
typedef int (*example_function)(int);

#include <stdio.h>
int main(){
	S_DSO_handl handler = S_DSO_load_file("./test.so");
	if(handler == NULL){
		printf("\t1 - error: %s\n", S_DSO_get_last_error());
		return 1;
	}
	S_DSO_func test_func = S_DSO_load_function(handler, "test_func");
	if(test_func == NULL){
		printf("\t2 - error: %s\n", S_DSO_get_last_error());
		return 2;
	}
	printf("%i\n", ((example_function)test_func)(2));
	if(S_DSO_close_file(handler) != 0){
		printf("\t3 - error: %s\n", S_DSO_get_last_error());
		return 3;
	}
	printf("%i\n", ((example_function)test_func)(-4));
	return 0;
}
*/
