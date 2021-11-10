#include <stdio.h>
#include "ft_malloc.h"

int main()
{
	void *x = malloc(10);
	printf("%p\n", x);
	return 0;
}
