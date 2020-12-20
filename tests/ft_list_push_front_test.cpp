extern "C"
{
#define new tripouille
#include "libasm.h"
#undef new
}

#include "sigsegv.hpp"
#include "check.hpp"

int iTest = 1;

void wrap_list_push_front(t_list **begin_list, void *data)
{
	int tripouille[42];
	ft_list_push_front(begin_list, data);
	tripouille[41] = 42;
}

int main(void)
{
	signal(SIGSEGV, sigsegv);
	CATEGORY("ft_list_push_front");

	t_list * list = NULL;
	wrap_list_push_front(&list, (void*)1);
	/* 1 */ check(list->data == (void*)1 && list->next == NULL);
	/* 2 */ mcheck(list, sizeof(t_list));
	wrap_list_push_front(&list, (void*)2);
	/* 3 */ check(list->data == (void*)2 && list->next->data == (void*)1 && list->next->next == NULL);
	lst_clean(&list);
	cout << ENDL;
	return (0);
}