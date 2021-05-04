extern "C"
{
#define new tripouille
#include "libasm.h"
#undef new
}

#include "sigsegv.hpp"
#include "check.hpp"

int iTest = 1;

int wrap_list_size(t_list *begin_list)
{
	int tripouille[42];
	int r = ft_list_size(begin_list);
	tripouille[41] = 42;
	return (r);
}

int main(void)
{
	signal(SIGSEGV, sigsegv);
	CATEGORY("ft_list_size")

	t_list * list = NULL;
	/* 1 */ check(wrap_list_size(list) == 0);
	ft_list_push_front(&list, (void*)1);
	/* 2 */ check(wrap_list_size(list) == 1);
	ft_list_push_front(&list, (void*)2);
	/* 3 */ check(wrap_list_size(list) == 2);
	for (long i = 0; i < 40; ++i) {
		ft_list_push_front(&list, (void*)(i + 3));
	}
	/* 4 */ check(wrap_list_size(list) == 42);
	lst_clean(&list);
	cout << ENDL;
	return (0);
}