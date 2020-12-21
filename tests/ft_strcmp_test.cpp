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

int wrap_strcmp(const char *s1, const char *s2)
{
	int tripouille[42];
	int r = ft_strcmp(s1, s2);
	tripouille[41] = 42;
	return (r);
}

int main(void)
{
	signal(SIGSEGV, sigsegv);
	CATEGORY("ft_strcmp");

	/* 1 */ check(wrap_strcmp("", "") == 0);
	/* 2 */ check(wrap_strcmp("Tripouille", "Tripouille") == 0);
	/* 3 */ check(wrap_strcmp("Tripouille", "tripouille") < 0);
	/* 4 */ check(wrap_strcmp("Tripouille", "TriPouille") > 0);
	/* 5 */ check(wrap_strcmp("Tripouille", "TripouillE") > 0);
	/* 6 */ check(wrap_strcmp("Tripouille", "TripouilleX") < 0);
	/* 7 */ check(wrap_strcmp("Tripouille", "Tripouill") > 0);
	cout << ENDL;
	return (0);
}