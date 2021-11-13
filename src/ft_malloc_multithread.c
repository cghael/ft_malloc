//
// Created by Cora Ghael on 11/13/21.
//

#include "ft_malloc.h"

int		secure_malloc()
{
	int		ret;
	t_info	*malloc_manager;

	malloc_manager = ft_get_malloc_manager();
	if (malloc_manager->init)
		return (0);
	malloc_manager->init = 1;
	ret = pthread_mutex_init(&malloc_manager->mutex, NULL);
	if (ret)
		return (ret);
	ret = pthread_mutex_lock(&malloc_manager->mutex);
	return (ret);
}

int		unsecure_malloc()
{
	int	ret;
	t_info	*malloc_manager;

	malloc_manager = ft_get_malloc_manager();
	if (!malloc_manager->init)
		return (0);
	malloc_manager->init = 0;
	ret = pthread_mutex_unlock(&(malloc_manager->mutex));
	return (ret);
}
