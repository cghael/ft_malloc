//
// Created by Cora Ghael on 11/10/21.
//

#include "ft_malloc.h"

/*
** по заданию у нас размер зоны должен быть кратным возвращаемому значению getpagesize()
** для этого мы округляем размер зоны в большую сторону
** пример:
** 			allowed_size + sizeof(t_zone) + sizeof(t_chunk) = 27
**			getpagesize() = 10
**			27 + 10 = 37 -> 37 / 10 = 3 -> 3 * 10 = 30 (30 > 27, так что все поместится и кратно 10)
*/

static size_t	get_small_tiny_zone_size(int status, size_t size, size_t page_size)
{
	size_t	zone_size;
	size_t	status_size;
	size_t	chunk_size;
	size_t	number_of_chunks;

	zone_size = page_size;
	status_size = (status == TINY) ? TINY_SIZE : SMALL_SIZE;
	chunk_size = sizeof(t_chunk) + status_size;
	number_of_chunks = (page_size - sizeof(t_zone)) / chunk_size;
	while (number_of_chunks < ALLOCATIONS_BY_ZONE)
	{
		number_of_chunks += (page_size - sizeof(t_zone)) / chunk_size;
		zone_size += page_size;
	}
	return (zone_size);
}

static size_t	get_large_zone_size(size_t size, size_t page_size)
{
	size_t	zone_size;

	zone_size = (size + sizeof(t_zone) + sizeof(t_chunk) + page_size) / page_size * page_size;
	return (zone_size);
}

size_t			ft_get_new_zone_size(int status, size_t size)
{
	size_t	zone_size;
	size_t	page_size;

	page_size =  getpagesize(); //todo понять что за пейдж сайз
	if (status == LARGE)
		zone_size = get_large_zone_size(size, page_size);
	else
		zone_size = get_small_tiny_zone_size(status, size, page_size);
	return (zone_size);
}
