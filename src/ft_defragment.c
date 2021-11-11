//
// Created by Cora Ghael on 11/11/21.
//

#include "ft_malloc.h"

static size_t	ft_list_size(t_chunk *start)
{
	size_t size;

	size = 0;
	while (start)
	{
		size++;
		start = start->next;
	}
	return (size);
}

static void	ft_unite_with_next_chunk(t_chunk *chunk)
{
	chunk->allowed_size += chunk->next->allowed_size + sizeof(t_chunk);
	chunk->next = chunk->next->next;
	if (chunk->next)
		chunk->next->prev->prev = chunk;
}

static void	ft_defragment_current_zone(t_zone *zone)
{
	t_chunk	*chunk;
	size_t	size;

	chunk = zone->free_start;
	size = ft_list_size(chunk);
	if (size > 1)		// если в зоне больше одного чанка свободно
	{
		while (chunk)
		{
			if (((uintptr_t)chunk + chunk->allowed_size + sizeof(t_chunk)) == (uintptr_t)chunk->next)
				ft_unite_with_next_chunk(chunk);
			if (chunk->prev
			&& ((uintptr_t)chunk->prev + chunk->prev->allowed_size + sizeof(t_chunk) == (uintptr_t)chunk))
			{
				chunk = chunk->prev;
				ft_unite_with_next_chunk(chunk);
			}
			chunk = chunk->next;
		}
	}
	if (size > 0)		// удалить зону если размер свободного чанка совпадает с зоной
	{

	}
}

void		ft_defragment()
{
	t_info *malloc_manager;
	t_zone *zone;

	malloc_manager = ft_get_malloc_manager();
	zone = malloc_manager->start;
	while (zone)
	{
		ft_defragment_current_zone(zone);
		zone = zone->next;
	}
}