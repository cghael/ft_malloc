//
// Created by Cora Ghael on 11/11/21.
//

#include "ft_malloc.h"

static void		print_head(t_zone *start)
{
	if (start->status == TINY)
		ft_putstr("TINY:  0x");
	else if (start->status == SMALL)
		ft_putstr("SMALL: 0x");
	else if (start->status == LARGE)
		ft_putstr("LARGE: 0x");
	else
		ft_putstr("FREE:  0x");
	ft_putadrr((size_t)start + sizeof(t_zone));
	ft_putchar('\n');
}

static void		print_current_chunk(t_chunk *current)
{
	ft_putstr("0x");
	ft_putadrr((size_t)current);
	ft_putstr(" - 0x");
	ft_putadrr((size_t)current + sizeof(t_chunk) + current->allowed_size - 1);
	ft_putstr(" : [");
	ft_putnbr(current->allowed_size);
	ft_putstr(" + ");
	ft_putnbr(sizeof(t_chunk));
	ft_putstr("] bytes\n");
}

static void		print_all_chunks(t_zone *zone)
{
	t_chunk *alloc;
	t_chunk *free;

	alloc = zone->alloc_start;
	free = zone->free_start;
	while (alloc || free)
	{
		if (alloc && free)
		{
			if ((uintptr_t)alloc < (uintptr_t)free)
			{
				ft_putstr("alloc: ");
				print_current_chunk(alloc);
				alloc = alloc->next;
			}
			else
			{
				ft_putstr("free:  ");
				print_current_chunk(free);
				free = free->next;
			}
		}
		else if (alloc)
		{
			ft_putstr("alloc: ");
			print_current_chunk(alloc);
			alloc = alloc->next;
		}
		else
		{
			ft_putstr("free:  ");
			print_current_chunk(free);
			free = free->next;
		}
	}
}

void			show_alloc_mem()
{
	t_info *malloc_manager;
	t_zone *tmp;

	malloc_manager = ft_get_malloc_manager();
	tmp = malloc_manager->start;
	if (tmp == NULL)
		return ;
	while (tmp)
	{
		print_head(tmp);
		print_all_chunks(tmp);
		ft_putchar('\n');
		tmp = tmp->next;
	}
}