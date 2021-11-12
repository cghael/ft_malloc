//
// Created by Cora Ghael on 11/9/21.
//

#include "ft_malloc.h"

void			*malloc(size_t size)
{
	void			*res;
	int				tmp_res;
	t_info			*malloc_manager;

	// todo проверка на мьютекс для бонусов

	res = NULL;
	if (size == 0)
		return (res);
	malloc_manager = ft_get_malloc_manager();
	tmp_res = ft_find_block_size(size, malloc_manager);							// проверяем, можно ли вообще выделить память такого размера
	if (tmp_res == EXIT_SUCCESS)												// если можно,
		res = ft_memory_allocation(size, malloc_manager->current_chunk);		// выделяем память
	return (res);
}