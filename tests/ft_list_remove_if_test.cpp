extern "C"
{
#define new tripouille
#include "libasm.h"
#undef new
}

#include "sigsegv.hpp"
#include "check.hpp"

int iTest = 1;

void wrap_list_remove_if(t_list **begin_list, void *data_ref, int (*cmp)(void*, void*),
								void (*free_fct)(void *))
{
	int tripouille[42];
	ft_list_remove_if(begin_list, data_ref, cmp, free_fct);
	tripouille[41] = 42;
}

int equal(void *d1, void *d2)
{return (*(char*)d1 - *(char*)d2);}

void remove(void *s)
{
	*(char*)s = 'X';
}

int main(void)
{
	signal(SIGSEGV, sigsegv);
	CATEGORY("ft_list_remove_if")

	t_list * list = NULL;
	char s[100] = {0}; char c = 0; char ref = 0;
	for (int i = 0; i < 10; ++i)
		s[i] = i + '0';
	wrap_list_remove_if(&list, &c, &equal, &remove);
	/* 1 */ check(list == NULL);

	ft_list_push_front(&list, &c);
	wrap_list_remove_if(&list, &ref, &equal, &remove);
	/* 2 */ check(list == NULL && c == 'X' && ref == 0);

	for (int i = 9; i >= 0; --i)
		ft_list_push_front(&list, s + i);

	ref = '0';
	wrap_list_remove_if(&list, &ref, &equal, &remove);
	t_list * tmp = list; string result;
	while(tmp != NULL)
	{
		result += *(char*)tmp->data;
		tmp = tmp->next;
	}
	/* 3 */ check(result == string("123456789") && s[0] == 'X' && ref == '0');


	ref = '9';
	wrap_list_remove_if(&list, &ref, &equal, &remove);
	tmp = list; result = "";
	while(tmp != NULL)
	{
		result += *(char*)tmp->data;
		tmp = tmp->next;
	}
	/* 4 */ check(result == string("12345678") && s[9] == 'X' && ref == '9');

	ref = '5';
	wrap_list_remove_if(&list, &ref, &equal, &remove);
	tmp = list; result = "";
	while(tmp != NULL)
	{
		result += *(char*)tmp->data;
		tmp = tmp->next;
	}
	/* 5 */ check(result == string("1234678") && s[5] == 'X' && ref == '5');
	lst_clean(&list);
	cout << ENDL;
	return (0);
}