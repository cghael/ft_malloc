//
// Created by Cora Ghael on 11/11/21.
//

#include "ft_malloc.h"

void			*ft_reallocate( size_t size, t_chunk *tmp_chunk, void *ptr)
{
	void	*new;
	size_t	cpy_size;
	void	*buffer;

	cpy_size = tmp_chunk->allowed_size > size ? size : tmp_chunk->allowed_size;
	buffer = malloc((cpy_size > SMALL_SIZE) ? size : SMALL_SIZE + 1);
	if (buffer == NULL)
		return (NULL);
	ft_memcpy(buffer, ptr, cpy_size);
	new = malloc(size);
	if (new)
		ft_memcpy(new, buffer, cpy_size);
	free(buffer);
	free(tmp_chunk);
	unsecure_malloc();
	return (new);
}

void			*realloc(void *ptr, size_t size)
{
	t_zone	*tmp_zone;
	t_chunk	*tmp_chunk;
	t_info	*malloc_manager;

	if (secure_malloc())
		return (NULL);
	if (ptr == NULL)
		return (malloc(size));
	if (size == 0)
	{
		free(ptr);
		return (malloc(size));
	}
	tmp_zone = ft_find_zone(ptr);
	if (tmp_zone == NULL)
	{
		unsecure_malloc();
		return (NULL);
	}
	tmp_chunk = ft_find_chunk_in_alloc_list(ptr, tmp_zone);
	malloc_manager = ft_get_malloc_manager();
	malloc_manager->current_zone = tmp_zone;
	malloc_manager->current_chunk = tmp_chunk;
	if (tmp_chunk != NULL)
	{
		ft_free_chunk(tmp_zone, tmp_chunk);
		ft_unite_with_next(tmp_chunk, tmp_zone);
		if (malloc_manager->current_chunk->allowed_size >= size)
		{
			ft_memory_allocation(size, malloc_manager->current_chunk);
			unsecure_malloc();
			return (ptr);
		}
		ft_unite_with_next(tmp_chunk->prev, tmp_zone);
		return (ft_reallocate(size, malloc_manager->current_chunk, ptr));
	}
	unsecure_malloc();
	return (NULL);
}
