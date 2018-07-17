#include "ALF_dso_loader.h"
#include <stdio.h>

ALF_DSO_handl ALF_DSO_load_file(const char *file){
	ALF_DSO_handl handler = NULL;
	#ifdef __WIN32__
		handler = (ALF_DSO_handl)LoadLibrary(file);
	#elif __unix__
		handler = (ALF_DSO_handl)dlopen(file, RTLD_LAZY);
	#endif
	return handler;
}

ALF_DSO_func ALF_DSO_load_function(ALF_DSO_handl handler, const char *function){
	ALF_DSO_func func = NULL;
	#ifdef __WIN32__
		func = (ALF_DSO_func)GetProcAddress((HMODULE)handler, function);
	#elif __unix__
		func = (ALF_DSO_func)dlsym(handler, function);
	#endif
	return func;
}

int ALF_DSO_close_file(ALF_DSO_handl handler){
	int retVal = 0;
	#ifdef __WIN32__
		retVal = !FreeLibrary((HMODULE)handler); // Returns nonzero in success
	#elif __unix__
		retVal = dlclose(handler);
	#endif
	return retVal;
}

char *ALF_DSO_get_last_error(void){
	char *result = NULL;

	#ifdef __WIN32__
		result = malloc(sizeof(char) * 32);
		sprintf(result, "%lu", GetLastError());
	#elif __unix__
		char *aux = dlerror();
		result = malloc(sizeof(char) * (strlen(aux) + 1));
		strcpy(result, aux);
	#endif

	return result;
}

/*
typedef int (*example_function)(int);

#include <stdio.h>
int main(){
	ALF_DSO_handl handler = S_DSO_load_file("./test.so");
	if(handler == NULL){
		printf("\t1 - error: %s\n", S_DSO_get_last_error());
		return 1;
	}
	ALF_DSO_func test_func = S_DSO_load_function(handler, "test_func");
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
