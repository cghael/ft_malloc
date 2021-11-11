#include "ft_malloc.h"

int main()
{
	void *x = malloc(10);
	void *y = malloc(11);
	void *z = malloc(12);
	void *l = malloc(600);
	show_alloc_mem();
	ft_putstr("-------------\n\n");
	free(y);
	show_alloc_mem();
	ft_putstr("-------------\n\n");
	free(x);
	show_alloc_mem();
	ft_putstr("-------------\n\n");
	free(z);
	show_alloc_mem();
	ft_putstr("-------------\n\n");
	free(l);
	show_alloc_mem();
	return 0;
}
