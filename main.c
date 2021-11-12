#include "ft_malloc.h"

int main()
{
	void *x = malloc(10);
	void *y = malloc(20);

	show_alloc_mem();
	char *s = malloc(10);
	s[9] = '\0';
	s[0] = 'a';
	s[1] = 'b';
	s[2] = 'c';
	s[3] = 'd';
	s[4] = 'e';
	s[5] = 'f';
	s[6] = 'g';
	s[7] = 'h';
	s[8] = 'j';
	ft_putstr(s);
	ft_putchar('\n');
	show_alloc_mem();

	char *p = realloc(s, 4);
	p[3] = '\0';
	ft_putstr(p);

	show_alloc_mem();
	free(y);
	show_alloc_mem();
	void *re1 = realloc(x, 31);
	show_alloc_mem();
	free(re1);
	show_alloc_mem();
	return 0;
}
