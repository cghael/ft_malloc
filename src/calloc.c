//
// Created by Cora Ghael on 11/11/21.
//

#include "ft_malloc.h"

void	*calloc(size_t num, size_t size)
{
	void	*new;

	if (num == 0 || size == 0)
		return (NULL);
	new = malloc(num * size);
	if (new == NULL)
		return (NULL);
	ft_bzero(new, size * num);
	return (new);
}
