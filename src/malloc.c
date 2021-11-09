//
// Created by Cora Ghael on 11/9/21.
//

#include "ft_malloc.h"

void 				*ft_memory_allocation(size_t size, t_info *malloc_manager)
{
	return (NULL);
}

void				*malloc(size_t size)
{
	void			*res;
	int				tmp_res;
	t_info			*malloc_manager;

	// todo проверка на мьютекс для бонусов

	res = NULL;
	malloc_manager = get_malloc_manager();
	tmp_res = ft_find_block_size(size, malloc_manager);		// проверяем, можно ли вообще выделить память такого размера
	if (tmp_res == EXIT_SUCCESS)								// если можно,
		res = ft_memory_allocation(size, malloc_manager);		// выделяем память
	return (res);
}