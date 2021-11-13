//
// Created by Cora Ghael on 11/10/21.
//

#include "ft_malloc.h"

static void		ft_unite_free_chunks(t_chunk *chunk, t_zone *current)
{
	if (chunk == NULL)
		return ;
	ft_unite_with_next(chunk, current);
	ft_unite_with_next(chunk->prev, current);
}

static void		ft_free_large_zone(t_zone *current)
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

static void		ft_free_zone_handler(t_zone *current)
{
	t_info *malloc_manager;
	t_zone *tmp;

	malloc_manager = ft_get_malloc_manager();
	tmp = malloc_manager->start;
	if (tmp == NULL)
		return ;
	if (tmp == current)
		malloc_manager->start = current->next;
	else
	{
		while (tmp->next != current && tmp->next != NULL)
			tmp = tmp->next;
		if (tmp->next == current)
		{
			tmp->next = current->next;
			munmap(current, current->size);
		}
	}
}

void			free(void *ptr)
{
	t_zone *current;
	t_chunk	*tmp;

	current = ft_find_zone(ptr);
	if (current != NULL)
	{
		if (current->status == LARGE)
			ft_free_large_zone(current);
		else
		{
			tmp = ft_find_chunk_in_alloc_list(ptr, current);
			ft_free_chunk(current, tmp);
			ft_unite_free_chunks(tmp, current);
			if (current->alloc_start == NULL)
				ft_free_zone_handler(current);
		}
	}
}
