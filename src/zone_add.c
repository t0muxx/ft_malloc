/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zone_add.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaraval <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 12:13:00 by tmaraval          #+#    #+#             */
/*   Updated: 2019/10/17 12:20:14 by tmaraval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

void		zone_fill_and_add(t_zone **zone, t_zone **new,
		size_t size, size_t pages_nbr)
{
	t_zone	*head;

	head = NULL;
	(*new)->size = size;
	(*new)->used = 0;
	(*new)->next = NULL;
	(*new)->prev = NULL;
	(*new)->pages_nbr = pages_nbr;
	(*new)->chunks = NULL;
	head = *zone;
	if (*zone == NULL)
		*zone = *new;
	else
	{
		while (head->next != NULL)
			head = head->next;
		head->next = *new;
		(*new)->prev = head;
	}
}

t_zone		*add_zone_large(t_zone **zone, size_t size)
{
	t_zone *new;
	size_t aligned;

	new = NULL;
	aligned = aligne_large(size + sizeof(t_zone));
	new = mmap(0, aligned,
		PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
	if (getenv("DEBUG_MMAP"))
	{
		ft_putstr("|DEBUG| -> mmaped size : ");
		ft_putnbr(aligned);
		ft_putendl("");
	}
	if (new == MAP_FAILED)
	{
		ft_putendl_fd("malloc : can't mmap memory for zone_tiny", 2);
		return (NULL);
	}
	ft_memset(new, 0, aligned);
	zone_fill_and_add(zone, &new, size, 0);
	return (new);
}

/*
** Add new zone, the 0x1000 here is for the t_zone struct
*/

int			add_zone(t_zone **zone, size_t pages_nbr)
{
	t_zone	*new;
	size_t	size;

	new = NULL;
	size = getpagesize() * pages_nbr;
	new = mmap(0, size,
			PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
	if (getenv("DEBUG_MMAP"))
	{
		ft_putstr("|DEBUG| -> mmaped size : ");
		ft_putnbr(size);
		ft_putendl("");
	}
	if (new == MAP_FAILED)
	{
		ft_putendl_fd("malloc : can't mmap memory for zone_tiny", 2);
		return (-1);
	}
	ft_memset(new, 0, size);
	ft_memset(new->state, USED, pages_nbr);
	zone_fill_and_add(zone, &new, size - sizeof(t_zone), pages_nbr);
	return (0);
}
