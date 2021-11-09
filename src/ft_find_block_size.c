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

static t_zone		*search_free_zone(size_t size, t_zone *start_zone)
{
	int		status;
	t_zone	*tmp;

	status = get_status(size);
	if (status == LARGE)
		return (NULL);
	if (start_zone == 0x0)
		return (NULL);
	tmp = start_zone;
	while (tmp != NULL)											// бежим по всем зонам
	{
		if ((tmp->status == status) &&							// ищем зону с нужным статусом
			(tmp->free_size >= (size + sizeof(t_alloc))))		// если в зоне достаточно места
				return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

/*
** по заданию у нас размер зоны должен быть кратным возвращаемому значению getpagesize()
** для этого мы округляем размер зоны в большую сторону
** пример:
** 			size + sizeof(t_zone) + sizeof(t_alloc) = 27
**			getpagesize() = 10
**			27 + 10 = 37 -> 37 / 10 = 3 -> 3 * 10 = 30 (30 > 27, так что все поместится и кратно 10)
*/

static size_t		get_zone_size(int status, size_t size)
{
	size_t	zone_size;
	size_t	page_size;
	size_t	chunk_size;
	size_t	status_size;
	size_t	number_of_chunks;

	page_size =  getpagesize(); //todo понять что за пейдж сайз
	if (status == LARGE)
	{
		zone_size = (size + sizeof(t_zone) + sizeof(t_alloc) + page_size) / page_size * page_size;
		return (zone_size);
	}
	zone_size = page_size;
	status_size = (status == TINY) ? TINY_SIZE : SMALL_SIZE;
	chunk_size = sizeof(t_alloc) + status_size;
	number_of_chunks = (page_size - sizeof(t_zone)) / chunk_size;
	while (number_of_chunks < ALLOCATIONS_BY_ZONE)
	{
		number_of_chunks += (page_size - sizeof(t_zone)) / chunk_size;
		zone_size += page_size;
	}
	return (zone_size);
}

static t_zone		*ft_allocate_new_zone(size_t size)
{
	int		status;
	t_zone	*tmp;
	size_t	zone_size;

	status = get_status(size);
	zone_size = get_zone_size(status, size);
	tmp = mmap(0, zone_size, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0); //todo разобраться с флагами
	if (tmp == NULL)
		return (NULL);
	tmp->status = status;
	tmp->size = zone_size;
	tmp->free_size = zone_size - sizeof(t_zone);
	tmp->start = (t_alloc*)(tmp + sizeof(t_zone));
	tmp->next = NULL;
	return (tmp);
}

int		ft_find_block_size(size_t size, t_info *malloc_manager)
{
	t_zone *current;

	current = search_free_zone(size, malloc_manager->start);
	if (current == NULL)
	{
		current = ft_allocate_new_zone(size);
		if (current == NULL)
			return (EXIT_FAILURE);
		//todo добавить в статическую структуру в список в куррент
	}
	return (EXIT_SUCCESS);
}