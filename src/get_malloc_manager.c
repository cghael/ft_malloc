//
// Created by Cora Ghael on 11/9/21.
//

#include "ft_malloc.h"

t_info		*get_malloc_manager()
{
	static t_info	malloc_manager;

	return (&malloc_manager);
}
