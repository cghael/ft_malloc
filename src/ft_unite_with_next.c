//
// Created by Cora Ghael on 11/12/21.
//

#include "ft_malloc.h"

void			ft_unite_with_next(t_chunk *current, t_zone *zone)
{
	t_chunk *next_chunk;
	t_chunk *alloc;

	alloc = zone->alloc_start;
	if (current == NULL)
		return ;
	next_chunk = current->next;
	while (alloc && ((uintptr_t)alloc < (uintptr_t)current))
		alloc = alloc->next;
	if (alloc == NULL)
	{
		current->allowed_size = (uintptr_t)zone + zone->size - (uintptr_t)current - sizeof(t_chunk);
		current->next = NULL;
	}
	else
	{
		current->allowed_size = (uintptr_t)alloc - (uintptr_t)current - sizeof(t_chunk);
		if (next_chunk)
		{
			while ((uintptr_t)next_chunk < (uintptr_t)alloc && next_chunk)
				next_chunk = next_chunk->next;
			if (next_chunk)
			{
				current->next = next_chunk;
				next_chunk->prev = current;
			}
		}
		else
			current->next = NULL;
	}
}
