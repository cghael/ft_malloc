//
// Created by Cora Ghael on 11/9/21.
//

#include "ft_malloc.h"

void				*malloc(size_t size)
{
	void			*res;
	int				tmp_res;
	static t_info	malloc_manager;

	// todo проверка на мьютекс для бонусов

	res = NULL;

	tmp_res = ft_find_block_size(size);							// проверяем, можно ли вообще выделить память такого размера
	if (tmp_res == EXIT_SUCCESS)								// если можно,
		res = memory_allocation(size, &malloc_manager);			// выделяем память
	return (res);
}