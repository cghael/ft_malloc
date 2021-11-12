//
// Created by Cora Ghael on 11/12/21.
//

#include "ft_malloc.h"

static void		ft_add_chunk_to_list(t_chunk *tmp)
{
	t_info *malloc_manager;

	malloc_manager = ft_get_malloc_manager();
	t_chunk *start = malloc_manager->current_zone->alloc_start;
	// нам надо перенести указатель на новую зону, которая станет занята в лист занятых зон
	// сначала ищем место

	if (start == NULL)
		malloc_manager->current_zone->alloc_start = tmp;
	else
	{
		if ((uintptr_t)tmp < (uintptr_t)start)
		{
			malloc_manager->current_zone->alloc_start = tmp;
			tmp->next = start;
			start->prev = tmp;
		}
		else
		{
			while(start->next != NULL && ((uintptr_t)tmp > (uintptr_t)start))
				start = start->next;
			if ((uintptr_t)tmp < (uintptr_t)start)
			{
				tmp->next = start;
				if (start->prev)
					start->prev->next = tmp;
				tmp->prev = start->prev;
				start->prev = tmp;
			}
			else
			{
				start->next = tmp;
				tmp->prev = start;
			}
		}
	}
}

void			*ft_memory_allocation(size_t size, t_chunk *free)
{
	t_chunk	*alloc;
	void	*res;
	t_info	*malloc_manager;

	malloc_manager = ft_get_malloc_manager();
	alloc = free;
	if (free->allowed_size >= (size + sizeof(t_chunk)))
	{
		free = (t_chunk *)((uint64_t)free + size + sizeof(t_chunk));
		free->next = alloc->next;
		free->prev = alloc->prev;
		if (free->next)
			free->next->prev = free;
		if (free->prev == NULL)
			malloc_manager->current_zone->free_start = free;
		else
			free->prev->next = free;
		free->allowed_size =
				alloc->allowed_size - size - sizeof(t_chunk);
	}
	else
	{
		if (free->prev == NULL)
			malloc_manager->current_zone->free_start = free->next;
		else
			free->prev->next = free->next;
		if (free->next)
			free->next->prev = free->prev;
	}
	alloc->allowed_size = size;
	alloc->next = NULL;
	alloc->prev = NULL;

	// сейчас лист фри готов
	// в лист аллок надо добавить alloc
	ft_add_chunk_to_list(alloc);
	res = (void*)((uintptr_t)alloc + sizeof(t_chunk));
	return (res);
}