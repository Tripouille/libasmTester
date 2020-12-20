extern "C"
{
#define new tripouille
#include "libasm.h"
#undef new
}

#include "sigsegv.hpp"
#include "check.hpp"

int iTest = 1;

int wrap_atoi_base(char *str, char *base)
{
	int tripouille[42];
	int r = ft_atoi_base(str, base);
	tripouille[41] = 42;
	return (r);
}

int main(void)
{
	signal(SIGSEGV, sigsegv);
	CATEGORY("ft_atoi_base");

	char * bin = (char*)"01";
	/* 1 */ check(wrap_atoi_base((char*)"0", bin) == 0);
	/* 2 */ check(wrap_atoi_base((char*)"+1", bin) == 1);
	/* 3 */ check(wrap_atoi_base((char*)"-1", bin) == -1);
	/* 4 */ check(wrap_atoi_base((char*)"10", bin) == 2);
	/* 5 */ check(wrap_atoi_base((char*)"101", bin) == 5);
	/* 6 */ check(wrap_atoi_base((char*)"1010", bin) == 10);
	/* 7 */ check(wrap_atoi_base((char*)"-1010", bin) == -10);
	char * dec = (char*)"0123456789";
	/* 8 */ check(wrap_atoi_base((char*)"0", dec) == 0);
	/* 9 */ check(wrap_atoi_base((char*)"+1", dec) == 1);
	/* 10 */ check(wrap_atoi_base((char*)"-1", dec) == -1);
	/* 11 */ check(wrap_atoi_base((char*)"9", dec) == 9);
	/* 12 */ check(wrap_atoi_base((char*)"-9", dec) == -9);
	/* 13 */ check(wrap_atoi_base((char*)"10", dec) == 10);
	/* 14 */ check(wrap_atoi_base((char*)"101", dec) == 101);
	/* 15 */ check(wrap_atoi_base((char*)"1010", dec) == 1010);
	/* 16 */ check(wrap_atoi_base((char*)"-1010", dec) == -1010);
	/* 17 */ check(wrap_atoi_base((char*)to_string(INT_MAX).c_str(), dec) == INT_MAX);
	/* 18 */ check(wrap_atoi_base((char*)to_string(INT_MIN).c_str(), dec) == INT_MIN);
	char * hex = (char*)"0123456789ABCDEF";
	/* 19 */ check(wrap_atoi_base((char*)"0", hex) == 0x0);
	/* 20 */ check(wrap_atoi_base((char*)"+1", hex) == 0x1);
	/* 21 */ check(wrap_atoi_base((char*)"-1", hex) == -0x1);
	/* 22 */ check(wrap_atoi_base((char*)"9", hex) == 0x9);
	/* 23 */ check(wrap_atoi_base((char*)"-9", hex) == -0x9);
	/* 24 */ check(wrap_atoi_base((char*)"10", hex) == 0x10);
	/* 25 */ check(wrap_atoi_base((char*)"101", hex) == 0x101);
	/* 26 */ check(wrap_atoi_base((char*)"1010", hex) == 0x1010);
	/* 27 */ check(wrap_atoi_base((char*)"-1010", hex) == -0x1010);
	/* 28 */ check(wrap_atoi_base((char*)"7FFFFFFF", hex) == INT_MAX);
	/* 29 */ check(wrap_atoi_base((char*)"-80000000", hex) == INT_MIN);
	/* Error */
	/* 30 */ check(wrap_atoi_base((char*)"2", bin) == 0);
	/* 31 */ check(wrap_atoi_base((char*)"1", (char*)"") == 0);
	/* 32 */ check(wrap_atoi_base((char*)"1", (char*)"1") == 0);
	/* 32 */ check(wrap_atoi_base((char*)"1", (char*)"1") == 0);
	/* 33 */ check(wrap_atoi_base((char*)"1", (char*)"001") == 0);
	/* 34 */ check(wrap_atoi_base((char*)"1", (char*)"011") == 0);
	/* 35 */ check(wrap_atoi_base((char*)"1", (char*)"01+") == 0);
	/* 36 */ check(wrap_atoi_base((char*)"1", (char*)"01-") == 0);
	/* 37 */ check(wrap_atoi_base((char*)"1", (char*)"01\t") == 0);
	/* 38 */ check(wrap_atoi_base((char*)"1", (char*)"01\n") == 0);
	/* 39 */ check(wrap_atoi_base((char*)"1", (char*)"01\v") == 0);
	/* 40 */ check(wrap_atoi_base((char*)"1", (char*)"01\f") == 0);
	/* 41 */ check(wrap_atoi_base((char*)"1", (char*)"01\r") == 0);
	/* 42 */ check(wrap_atoi_base((char*)"", bin) == 0);
	char s8[] = {'0', '1', 8, 0}; char s14[] = {'0', '1', 14, 0}; char * gap = (char*)"0123450";
	/* 43 */ check(wrap_atoi_base((char*)"1", s8) == 1);
	/* 44 */ check(wrap_atoi_base((char*)"1", s14) == 1);
	/* 45 */ check(wrap_atoi_base((char*)"1", gap) == 0);
	cout << ENDL;
	return (0);
}