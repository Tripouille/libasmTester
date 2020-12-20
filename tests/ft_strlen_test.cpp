extern "C"
{
#define new tripouille
#include "libasm.h"
#undef new
}

#include "sigsegv.hpp"
#include "check.hpp"

int iTest = 1;

size_t wrap_strlen(char const * s)
{
	int tripouille[42];
	size_t r = ft_strlen(s);
	tripouille[41] = 42;
	return (r);
}

int main(void)
{
	signal(SIGSEGV, sigsegv);
	CATEGORY("ft_strlen");

	/* 1 */ check(wrap_strlen("123") == 3);
	/* 2 */ check(wrap_strlen("") == 0);
	cout << ENDL;
	return (0);
}