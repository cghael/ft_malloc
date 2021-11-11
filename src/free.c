//
// Created by Cora Ghael on 11/10/21.
//

#include "ft_malloc.h"

static void		ft_get_chunk_to_free_list(t_chunk *tmp, t_zone *current)
{
	t_chunk *start;

	start = current->free_start;
	if (start == NULL)
		current->free_start = tmp;
	else if ((uintptr_t)start > (uintptr_t)tmp)
	{
		current->free_start = tmp;
		tmp->next = start;
		start->prev = tmp;
	}
	else
	{
		while (((uintptr_t)start < (uintptr_t)tmp) && start->next != NULL)
			start = start->next;
		if ((uintptr_t)start > (uintptr_t)tmp)
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

	tmp = ft_find_chunk_in_alloc_list(ptr, current);
	if (tmp == NULL)
		return ;
	if (tmp->prev == NULL)
	{
		current->alloc_start = tmp->next;
		if (tmp->next)
			tmp->next->prev = NULL;
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
	ft_defragment();
}
