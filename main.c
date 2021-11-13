#include "ft_malloc.h"
#include <string.h>

void *foo()
{
	void *res;

	res = malloc(100 * 1024);
	show_alloc_mem();
	free(res);
	return (NULL);
}

int main()
{
	int		i = 0;
	int		size = 4;
	char	**addr;


	ft_putstr("- - - - - - PART ONE - - - - - -\n");
	addr = (char**)malloc(sizeof(char**) * size);
	show_alloc_mem();
	while (i < size)
	{
		addr[i] = (char*)malloc(1000 + i);
		addr[i][0] = 21 + i;
		show_alloc_mem();
		ft_putstr("addr[i][0] = ");
		ft_putnbr(addr[i][0]);
		ft_putchar('\n');
		i++;
	}
	i = 0;
	while (i < size)
	{
		free(addr[i]);
		show_alloc_mem();
		i++;
	}
	free(addr);
	show_alloc_mem();


	ft_putstr("- - - - - - - - - PART TWO - - - - - - - - -\n");
	void *x = malloc(10);
	char *y = malloc(20);
	void *z = malloc(20);
	show_alloc_mem();
	y[0] = 'p';
	y[1] = 'i';
	y[2] = 'p';
	y[3] = 'a';
	y[4] = '\0';
	ft_putstr("\nShow y mem : ");
	ft_putstr(y);
	ft_putchar('\n');
	free(x);
	show_alloc_mem();
	char *ptr = realloc(y, 25);
	ptr[1] = 'u';
	show_alloc_mem();
	ft_putstr("\nShow ptr mem : ");
	ft_putstr(ptr);
	ft_putchar('\n');
	free(ptr);
	show_alloc_mem();
	free(z);
	show_alloc_mem();

	ft_putstr("- - - - - - - - - PART THREE - - - - - - - - -\n");
	x = malloc(SMALL_SIZE + 100);
	y = malloc(SMALL_SIZE + 200);
	show_alloc_mem();
	free(x);
	free(y);
	show_alloc_mem();

	ft_putstr("- - - - - - - - - PART FOUR - - - - - - - - -\n");
	x = calloc(8, 100);
	show_alloc_mem();
	free(x);

	ft_putstr("- - - - - - - - - PART FOUR - - - - - - - - -\n");
	x = (char*)malloc(16 * 1024 * 1024);
	show_alloc_mem();
	strcpy(x, "lol kek\n");
	ft_putstr(x);
	y = (char*)realloc(x, 128 * 1024 * 1024);
	y[127 * 1024 * 1024] = 42;
	ft_putstr(y);
	show_alloc_mem();
	free(y);
	show_alloc_mem();

	ft_putstr("- - - - - - - - - PART FIVE - - - - - - - - -\n");
	x = malloc(16);
	show_alloc_mem();
	free(NULL);
	free((void *)x + 5);
	show_alloc_mem();
	if (realloc((void *)x + 5, 10) == NULL)
		ft_putstr("lol kek\n");

	ft_putstr("- - - - - - - - - PART SIX - - - - - - - - -\n");
	x = malloc(1024);
	y = malloc(1024 * 32);
	z = malloc(1024 * 1024);
	ptr = malloc(1024 * 1024 * 128);
	show_alloc_mem();
	free(x);
	free(y);
	free(z);
	free(ptr);
	show_alloc_mem();

	ft_putstr("- - - - - - - - - PART SEVEN - - - - - - - - -\n");
	pthread_t	thread1;
	pthread_t	thread2;

	pthread_create(&thread1, NULL, foo, NULL);
	pthread_create(&thread2, NULL, foo, NULL);
	pthread_join(thread1, NULL);
	pthread_join(thread2, NULL);
	show_alloc_mem();

	return 0;
}
