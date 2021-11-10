//
// Created by Cora Ghael on 11/10/21.
//

#include "ft_malloc.h"

static void		ft_get_chunk_to_free_list(t_chunk *tmp, t_zone *current)
{
	t_chunk *start;

	start = current->free_start;
	if ((uintptr_t)start > (uintptr_t)tmp)
	{
		current->free_start = tmp;
		tmp->next = start;
		start->prev = tmp;
	}
	else
	{
		while (((uintptr_t)start < (uintptr_t)tmp) && start->next != NULL)
			start = start->next;
		if (start->next != NULL)
		{
			start->prev->next = tmp;
			tmp->prev = start->prev;
			start->prev = tmp;
			tmp->next = start;
		}
		else
		{
			start->next = tmp;
			tmp->prev = start;
		}
	}
}

static void		ft_free_small_zone(t_zone *current, void *ptr)
{
	t_chunk *tmp;

	tmp = current->alloc_start;
	while (((uintptr_t)tmp < (uintptr_t)ptr) && tmp != NULL)
		tmp = tmp->next;
	if (tmp == NULL)
		return ;
	tmp = tmp->prev;
	if (tmp->prev == NULL)
	{
		tmp->next->prev = NULL;
		current->alloc_start = tmp->next;
		tmp->next = NULL;
	}
	else
	{
		tmp->prev->next = tmp->next;
		tmp->next->prev = tmp->prev;
		tmp->next = NULL;
		tmp->prev = NULL;
	}
	ft_get_chunk_to_free_list(tmp, current);
}

static void		ft_free_large_zone(t_zone *current, void *ptr)
{
	t_info	*malloc_manager;
	t_zone	*tmp;

	malloc_manager = ft_get_malloc_manager();
	tmp = malloc_manager->start;
	if (current == tmp)
	{
		malloc_manager->start = tmp->next;
	}
	else
	{
		while (tmp->next != current)
			tmp = tmp->next;
		tmp->next = current->next;
	}
	munmap(current, current->size);
}

static t_zone	*ft_find_zone(void *ptr)
{
	t_zone *tmp;
	t_info *malloc_manager;

	tmp = NULL;
	malloc_manager = ft_get_malloc_manager();
	if (ptr != NULL && malloc_manager->start != 0x0)
	{
		tmp = malloc_manager->start;
		while (tmp != NULL)
		{
			if ((uintptr_t)tmp < (uintptr_t)ptr
			&& ((uintptr_t)tmp + tmp->size > (uintptr_t)ptr))
				break ;
			tmp = tmp->next;
		}
	}
	return (tmp);
}

void			free(void *ptr)
{
	t_zone *current;

	current = ft_find_zone(ptr);
	if (current != NULL)
	{
		if (current->status == LARGE)
			ft_free_large_zone(current, ptr);
		else
			ft_free_small_zone(current, ptr);
	}
}
