//
// Created by Cora Ghael on 11/11/21.
//

#include "ft_malloc.h"

int		ft_get_status(size_t size)
{
	if (size <= TINY_SIZE)
		return (TINY);
	if (size <= SMALL_SIZE)
		return (SMALL);
	return (LARGE);
}

t_info		*ft_get_malloc_manager()
{
	static t_info	malloc_manager;

	return (&malloc_manager);
}

t_zone	*ft_find_zone(void *ptr)
{
	t_zone *tmp;
	t_info *malloc_manager;

	tmp = NULL;
	malloc_manager = ft_get_malloc_manager();
	if (ptr != NULL && malloc_manager->start != 0x0)
	{
		tmp = malloc_manager->start;
		while (tmp != NULL)
		{
			if ((uintptr_t)tmp < (uintptr_t)ptr
				&& ((uintptr_t)tmp + tmp->size > (uintptr_t)ptr))
				break ;
			tmp = tmp->next;
		}
	}
	return (tmp);
}

t_chunk	*ft_find_chunk_in_alloc_list(void *ptr, t_zone *tmp_zone)
{
	t_chunk	*tmp;

	tmp = tmp_zone->alloc_start;
	while (tmp != NULL)
	{
		if ((uintptr_t)tmp <= (uintptr_t)ptr
		&& ((uintptr_t)tmp + sizeof(t_chunk) + tmp->allowed_size >= (uintptr_t)ptr))
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t i;

	i = 0;
	while (i < n)
	{
		((unsigned char*)dst)[i] = ((unsigned char*)src)[i];
		i++;
	}
	return (dst);
}

void	ft_bzero(void *s, size_t n)
{
	size_t i;

	i = 0;
	if (n != 0)
	{
		while (i < n)
		{
			((unsigned char *)s)[i] = (unsigned char)0;
			i++;
		}
	}
}

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	ft_putstr(const char *s)
{
	int i;

	i = 0;
	while (s[i])
		i++;
	write(1, s, i);
}

void	ft_putadrr(size_t addr)
{
	char base[16] = "0123456789ABCDEF";
	if (addr > 16)
		ft_putadrr(addr / 16);
	ft_putchar(base[addr % 16]);
}

void	ft_putnbr(size_t n)
{
	unsigned int nb;

	nb = n;
	if (n < 0)
	{
		ft_putchar('-');
		nb = -nb;
	}
	if (nb <= 9)
		ft_putchar('0' + nb);
	else
	{
		ft_putnbr(nb / 10);
		ft_putchar('0' + nb % 10);
	}
}
