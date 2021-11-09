#include <stdio.h>
#include "ft_malloc.h"

int main()
{
	int x = getpagesize();
	printf("%d\n", x);
	return 0;
}
