//
// Created by Cora Ghael on 11/11/21.
//

#include "ft_malloc.h"

static void		print_head(t_zone *start)
{
	if (start->status == TINY)
		ft_putstr("\033[0;33mTINY:  0x");
	else if (start->status == SMALL)
		ft_putstr("\033[0;33mSMALL: 0x");
	else if (start->status == LARGE)
		ft_putstr("\033[0;33mLARGE: 0x");
	else
		ft_putstr("\033[0;33mFREE:  0x");
	ft_putadrr((size_t)start + sizeof(t_zone));
	ft_putstr("\033[0m\n");
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
				ft_putstr("\033[0;31malloc:\033[0m ");
				print_current_chunk(alloc);
				alloc = alloc->next;
			}
			else
			{
				ft_putstr("\033[0;32mfree :\033[0m ");
				print_current_chunk(free);
				free = free->next;
			}
		}
		else if (alloc)
		{
			ft_putstr("\033[0;31malloc:\033[0m ");
			print_current_chunk(alloc);
			alloc = alloc->next;
		}
		else
		{
			ft_putstr("\033[0;32mfree :\033[0m ");
			print_current_chunk(free);
			free = free->next;
		}
	}
}

static void		ft_print_zone(t_zone *current)
{
	t_chunk	*tmp;
	size_t	size;
	size_t	n_chunk;

	size = 0;
	n_chunk = 0;
	tmp = current->alloc_start;
	while (tmp)
	{
		n_chunk += 1;
		size += tmp->allowed_size;
		tmp = tmp->next;
	}
	ft_putstr("\n");
	ft_putstr("Total bytes alloc : [");
	ft_putnbr(sizeof(t_zone));
	ft_putstr(" + ");
	ft_putnbr(size);
	ft_putstr(" + ");
	ft_putnbr(n_chunk * sizeof(t_chunk));
	ft_putstr("]\n");

	n_chunk = 0;
	size = 0;
	tmp = current->free_start;
	while (tmp)
	{
		n_chunk += 1;
		size += tmp->allowed_size;
		tmp = tmp->next;
	}
	ft_putstr("Total bytes free  : [");
	ft_putnbr(size);
	ft_putstr(" + ");
	ft_putnbr(n_chunk * sizeof(t_chunk));
	ft_putstr("]\n\n\n");
}

static void		ft_print_total(t_zone *tmp)
{
	size_t size;

	size = 0;
	while (tmp)
	{
		size += tmp->size;
		tmp = tmp->next;
	}
	ft_putstr("Total : ");
	ft_putnbr(size);
	ft_putstr("\n\n");
}

void			show_alloc_mem()
{
	t_info *malloc_manager;
	t_zone *tmp;

	malloc_manager = ft_get_malloc_manager();
	tmp = malloc_manager->start;
	if (tmp == NULL)
	{
		ft_putstr("NO ALLOCATED MEMORY\n");
		ft_putstr("\n******************************\n\n");
		return;
	}
	ft_putstr("\n");
	while (tmp)
	{
		print_head(tmp);
		print_all_chunks(tmp);
		ft_print_zone(tmp);
		tmp = tmp->next;
	}
	ft_print_total(malloc_manager->start);
	ft_putstr("\n******************************\n\n");
}