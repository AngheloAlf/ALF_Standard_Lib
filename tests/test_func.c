/* gcc test.c -o test.so -shared -Wall -fPIC */

int test_func(int x){
	if(x < 0){
		return x*x*x;
	}
	return x*x;
}