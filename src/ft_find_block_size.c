//
// Created by Cora Ghael on 11/9/21.
//

#include "ft_malloc.h"

static int		get_status(size_t size)
{
	if (size <= TINY_SIZE)
		return (TINY);
	if (size <= SMALL_SIZE)
		return (SMALL);
	return (LARGE);
}

static t_zone		*search_free_zone(size_t size, t_info *malloc_manager)
{
	int		status;
	t_zone	*tmp;
	t_chunk	*tmp_chunk;

	status = get_status(size);
	if (status == LARGE)
		return (NULL);
	if (malloc_manager->start == 0x0)
		return (NULL);
	tmp = malloc_manager->start;
	while (tmp != NULL)									// бежим по всем зонам
	{
		if (tmp->status == status)						// ищем зону с нужным статусом
		{
			tmp_chunk = tmp->free_start;
			while(tmp_chunk != NULL)
			{
				if (tmp_chunk->allowed_size >= size)
				{
					malloc_manager->current_chunk = tmp_chunk;
					return (tmp);
				}
				tmp_chunk = tmp_chunk->next;
			}
		}
		tmp = tmp->next;
	}
	return (NULL);
}

static void			ft_add_zone_to_manager(t_info *malloc_manager, t_zone *current)
{
	t_zone *tmp;
	t_zone *prev_tmp;

	if (malloc_manager->start == NULL)				// если еще ни одной зоны нет
		malloc_manager->start = current;
	else
	{
		tmp = malloc_manager->start;
		prev_tmp = NULL;
		if ((uintptr_t)tmp > (uintptr_t)current)	// если адрес новой зоны меньше адреса start
		{
			current->next = tmp;
			malloc_manager->start = current;
		}
		else
		{
			while ((uintptr_t)tmp < (uintptr_t)current && tmp->next != NULL)
			{
				prev_tmp = tmp;
				tmp = tmp->next;
			}
			if (tmp->next != NULL)
			{
				if (prev_tmp != NULL)
					prev_tmp->next = current;
				current->next = tmp;
			}
			else
				tmp->next = current;
		}
	}
}

static t_zone		*ft_allocate_new_zone(size_t size)
{
	int		status;
	t_zone	*tmp;
	size_t	zone_size;

	status = get_status(size);
	zone_size = ft_get_new_zone_size(status, size);
	tmp = mmap(0, zone_size, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0); //todo разобраться с флагами
	if (tmp == NULL)
		return (NULL);
	tmp->status = status;
	tmp->size = zone_size;
	tmp->alloc_start = NULL;
	tmp->free_start = (t_chunk*)(tmp + sizeof(t_zone));
	tmp->free_start->allowed_size = tmp->size - sizeof(t_zone) - sizeof(t_chunk);
	tmp->free_start->next = tmp->free_start;
	tmp->free_start->prev = tmp->free_start;
	tmp->next = NULL;
	return (tmp);
}

int		ft_find_block_size(size_t size, t_info *malloc_manager)
{
	t_zone *current;

	current = search_free_zone(size, malloc_manager);
	if (current == NULL)
	{
		current = ft_allocate_new_zone(size);
		if (current == NULL)
			return (EXIT_FAILURE);
		ft_add_zone_to_manager(malloc_manager, current);
		malloc_manager->current_chunk = current->free_start;
	}
	malloc_manager->current_zone = current;
	return (EXIT_SUCCESS);
}