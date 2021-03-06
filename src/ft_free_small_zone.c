//
// Created by Cora Ghael on 11/12/21.
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

void			ft_free_chunk(t_zone *current, t_chunk *tmp)
{
	if (tmp == NULL)
		return ;
	if (tmp->prev == NULL)
	{
		current->alloc_start = tmp->next;
		if (current->alloc_start)
			current->alloc_start->prev = NULL;
		tmp->next = NULL;
	}
	else
	{
		tmp->prev->next = tmp->next;
		if (tmp->next)
			tmp->next->prev = tmp->prev;
		tmp->next = NULL;
		tmp->prev = NULL;
	}
	ft_get_chunk_to_free_list(tmp, current);
}
