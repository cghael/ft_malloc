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

typedef struct		s_chunk
{
	uint64_t		allowed_size;			// размер, который можно отдать программе
	struct s_chunk	*next;
	struct s_chunk	*prev;
}					t_chunk;

/*
** Зона памяти:	свойства зарезервированной область, в которой можно выделять
**				участки памяти TINY_SIZE или SMALL_SIZE или один участок LARGE
**
** Если тип зоны TINY или SMALL, то там должно быть не менее ALLOCATIONS_BY_ZONE
** выделений (условие сабжекта, для минимизации сисколов)
*/

typedef struct		s_zone
{
	unsigned int	status;			// ТИНИ, СМОЛ или ЛАРДЖ
	uint64_t		size;			// количесто байт всего в зоне
	t_chunk			*free_start;
	t_chunk			*alloc_start;
	struct s_zone	*next;
}					t_zone;

/*
** Статическая переменная для менеджмента информации о выделенных участках памяти
*/

typedef struct		s_info
{
	t_zone			*start;
	t_zone			*current_zone;
	t_chunk			*current_chunk;
}					t_info;


/*
** -------------------------------- functions ----------------------------------
*/

t_info				*ft_get_malloc_manager();
int					ft_get_status(size_t size);
t_zone				*ft_find_zone(void *ptr);
t_chunk				*ft_find_chunk_in_alloc_list(void *ptr, t_zone *tmp_zone);
void				*ft_memcpy(void *dst, const void *src, size_t n);
void				ft_bzero(void *s, size_t n);
void				ft_putchar(char c);
void				ft_putstr(const char *s);
void				ft_putadrr(size_t addr);
void				ft_putnbr(size_t n);

void				*malloc(size_t size);
int					ft_find_block_size(size_t size, t_info *malloc_manager);
size_t				ft_get_new_zone_size(int status, size_t size);

void				free(void *ptr);

void				*realloc(void *ptr, size_t size);

void				*calloc(size_t num, size_t size);

void				show_alloc_mem();

#endif //FT_MALLOC_H
