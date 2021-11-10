#include <stdio.h>
#include "ft_malloc.h"

int main()
{
	void *x = malloc(67890);
	printf("%p\n", x);
	free(x);
	return 0;
}
