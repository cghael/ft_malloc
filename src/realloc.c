//
// Created by Cora Ghael on 11/11/21.
//

#include "ft_malloc.h"

void			*ft_reallocate( size_t size, t_chunk *tmp_chunk)
{
	void	*new;
	size_t	cpy_size;

	cpy_size = tmp_chunk->allowed_size > size ? size : tmp_chunk->allowed_size;
	new = malloc(size);
	if (new)
		ft_memcpy(new, tmp_chunk + sizeof(t_chunk), cpy_size);
	return (new);
}

void			*realloc(void *ptr, size_t size)
{
	t_zone	*tmp_zone;
	t_chunk	*tmp_chunk;
	t_info	*malloc_manager;

	if (ptr == NULL)
		return (malloc(size));
	if (size == 0)
	{
		free(ptr);
		return (malloc(size));
	}
	tmp_zone = ft_find_zone(ptr);
	tmp_chunk = ft_find_chunk_in_alloc_list(ptr, tmp_zone);
	malloc_manager = ft_get_malloc_manager();
	malloc_manager->current_zone = tmp_zone;
	malloc_manager->current_chunk = tmp_chunk;
	if (tmp_chunk != NULL)
	{
		ft_free_chunk(tmp_zone, tmp_chunk, ptr);
		ft_unite_with_next(tmp_chunk, tmp_zone);
		if (malloc_manager->current_chunk->allowed_size >= size)
		{
			ft_memory_allocation(size, malloc_manager->current_chunk);
			return (ptr);
		}
		show_alloc_mem();
		return (ft_reallocate(size, malloc_manager->current_chunk));
	}
	return (NULL);
}
