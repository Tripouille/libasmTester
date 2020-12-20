extern "C"
{
#define new tripouille
#include "libasm.h"
#undef new
}

#include "sigsegv.hpp"
#include "check.hpp"
#include <string.h>
#include <unistd.h>


int iTest = 1;

char * wrap_strdup(const char *s1)
{
	int tripouille[42];
	char * r = ft_strdup(s1);
	tripouille[41] = 42;
	return (r);
}

int main(void)
{
	signal(SIGSEGV, sigsegv);
	CATEGORY("ft_strdup");

	char const * src = ""; char * s = wrap_strdup(src); 
	/* 1 */ check(!strcmp(s, src));
	/* 2 */ mcheck(s, strlen(src) + 1); free(s);

	src = "1"; s = wrap_strdup(src); 
	/* 3 */ check(!strcmp(s, src));
	/* 4 */ mcheck(s, strlen(src) + 1); free(s);

	src = "123"; s = wrap_strdup(src); 
	/* 5 */ check(!strcmp(s, src));
	/* 6 */ mcheck(s, strlen(src) + 1); free(s);
	cout << ENDL;
	return (0);
}