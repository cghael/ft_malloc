//
// Created by Cora Ghael on 11/13/21.
//

#include "ft_malloc.h"

int		secure_malloc()
{
	int		ret;
	t_info	*malloc_manager;

	malloc_manager = ft_get_malloc_manager();
	ret = pthread_mutex_lock(&malloc_manager->mutex);
	return (ret);
}

int		unsecure_malloc()
{
	int	ret;
	t_info	*malloc_manager;

	malloc_manager = ft_get_malloc_manager();
	ret = pthread_mutex_unlock(&malloc_manager->mutex);
	return (ret);
}
