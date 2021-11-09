//
// Created by Cora Ghael on 11/9/21.
//

#ifndef FT_MALLOC_H
#define FT_MALLOC_H

/*
** --------------------------------- includes ----------------------------------
*/

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <sys/mman.h>
# include <inttypes.h>

/*
** --------------------------------- defines -----------------------------------
*/

# define NOT_ALLOCATED			0
# define ALLOCATED				1

# define TINY_SIZE				512
# define SMALL_SIZE				1024
# define TINY					0
# define SMALL					1
# define LARGE					2
# define ALLOCATIONS_BY_ZONE	100

/*
** --------------------------------- structs -----------------------------------
*/

/*
** Участок памяти:	свойства области памяти,
**					выделенной для программы
*/

typedef struct		s_alloc
{
	unsigned char	status;			// занято или не занято
	unsigned int	size;			// размер, который выделился
	struct s_alloc	*next;
}					t_alloc;

/*
** Зона памяти:	свойства зарезервированной область, в которой можно выделять
**				участки памяти TINY_SIZE или SMALL_SIZE или один участок LARGE
**
** Если тип зоны TINY или SMALL, то там должно быть не менее ALLOCATIONS_BY_ZONE
** выделений (условие сабжекта, для минимизации сисколов)
*/

typedef struct		s_zone
{
	t_alloc			*start;			// начало первого выделенного участка в зоне
	unsigned int	status;			// ТИНИ, СМОЛ или ЛАРДЖ
	unsigned int	free_size;		// сколько осталось пустого места в одной зоне
	unsigned int	size;			// количесто байт всего в зоне
	struct s_zone	*next;
}					t_zone;

/*
** Статическая переменная для менеджмента информации о выделенных участках памяти
*/

typedef struct		s_info
{
	t_zone			*start;
	t_zone			*current;
}					t_info;


/*
** -------------------------------- functions ----------------------------------
*/

t_info				*get_malloc_manager();
void				*malloc(size_t size);
int					ft_find_block_size(size_t size, t_info *malloc_manager);
void				*ft_memory_allocation(size_t size, t_info *malloc_manager);

#endif //FT_MALLOC_H
