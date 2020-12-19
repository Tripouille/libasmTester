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
	cout << FG_LGRAY << "ft_strcmp\t: ";

	/* 1 */ check(wrap_strcmp("", "") == 0);
	/* 2 */ check(wrap_strcmp("Tripouille", "Tripouille") == 0);
	/* 3 */ check(wrap_strcmp("Tripouille", "tripouille") == 'T' - 't');
	/* 4 */ check(wrap_strcmp("Tripouille", "TriPouille") == 'p' - 'P');
	/* 5 */ check(wrap_strcmp("Tripouille", "TripouillE") == 'e' - 'E');
	/* 6 */ check(wrap_strcmp("Tripouille", "TripouilleX") == -'X');
	/* 7 */ check(wrap_strcmp("Tripouille", "Tripouill") == 'e');
	cout << ENDL;
	return (0);
}