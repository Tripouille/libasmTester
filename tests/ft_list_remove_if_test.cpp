extern "C"
{
#define new tripouille
#include "libasm.h"
#undef new
}

#include "sigsegv.hpp"
#include "check.hpp"

int iTest = 1;

void wrap_list_sort(t_list **begin_list, int (*cmp)(void*, void*))
{
	int tripouille[42];
	ft_list_sort(begin_list, cmp);
	tripouille[41] = 42;
}

int lower(void *d1, void *d2)
{return ((long long)d1 > (long long)d2);}

int main(void)
{
	signal(SIGSEGV, sigsegv);
	CATEGORY("ft_list_sort")

	t_list * list = NULL;
	wrap_list_sort(&list, &lower);
	/* 1 */ check(list == NULL);

	ft_list_push_front(&list, (void*)1);
	wrap_list_sort(&list, &lower);
	/* 2 */ check(list->data == (void*)1);

	ft_list_push_front(&list, (void*)2);
	ft_list_push_front(&list, (void*)3);
	ft_list_push_front(&list, (void*)4);
	ft_list_push_front(&list, (void*)-1);
	ft_list_push_front(&list, (void*)5);
	ft_list_push_front(&list, (void*)-2);
	ft_list_push_front(&list, (void*)6);
	ft_list_push_front(&list, (void*)-3);
	ft_list_push_front(&list, (void*)7);
	ft_list_push_front(&list, (void*)0);
	wrap_list_sort(&list, &lower); t_list * tmp = list; string result;
	while(tmp != NULL)
	{
		result += to_string((long long)tmp->data);
		tmp = tmp->next;
	}
	/* 3 */ check(result == string("-3-2-101234567"));
	lst_clean(&list);
	cout << ENDL;
	return (0);
}