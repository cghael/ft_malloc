#include <stdio.h>
//# include <stdlib.h>
#include "ft_malloc.h"

int main()
{
	void *x = malloc(999999999999999999);
	printf("%p\n", x);
	free(x);
	return 0;
}
