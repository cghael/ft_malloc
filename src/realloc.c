//
// Created by Cora Ghael on 11/11/21.
//

#include "ft_malloc.h"

void			*ft_reallocate(t_chunk *tmp_chunk, size_t size)
{
	void	*new;
	size_t	cpy_size;

	cpy_size = tmp_chunk->allowed_size > size ? size : tmp_chunk->allowed_size;
	new = malloc(size);
	if (new)
	{
		ft_memcpy(new, tmp_chunk + sizeof(t_chunk), cpy_size);
		free(tmp_chunk + sizeof(t_chunk));
	}
	return (new);
}

void			*realloc(void *ptr, size_t size)
{
	t_zone	*tmp_zone;
	t_chunk	*tmp_chunk;
	int		status;

	if (ptr == NULL)
		return (malloc(size));
	if (size == 0)
	{
		free(ptr);
		return (malloc(size));
	}
	tmp_zone = ft_find_zone(ptr);
	tmp_chunk = ft_find_chunk_in_alloc_list(ptr, tmp_zone);
	if (tmp_chunk != NULL)
	{
		status = ft_get_status(size);
		if (status != LARGE && tmp_chunk->allowed_size >= size)
		{
			tmp_chunk->allowed_size = size;
			return (ptr);
		}
		return (ft_reallocate(tmp_chunk, size));
	}
	return (NULL);
}
