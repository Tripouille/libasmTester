extern "C"
{
#define new tripouille
#include "libasm.h"
#undef new
}

#include "sigsegv.hpp"
#include "check.hpp"
#include "string.h"

int iTest = 1;

char * wrap_strcpy(char *dst, const char *src)
{
	int tripouille[42];
	char * r = ft_strcpy(dst, src);
	check(r == dst);
	tripouille[41] = 42;
	return (r);
}

int main(void)
{
	signal(SIGSEGV, sigsegv);
	CATEGORY("ft_strcpy");

	char buffer[100] = {0};
	/* 1-2 */ check(!strcmp(wrap_strcpy(buffer, "123"), "123"));
	/* 3-4 */ check(!strcmp(wrap_strcpy(buffer, ""), ""));
	cout << ENDL;
	return (0);
}