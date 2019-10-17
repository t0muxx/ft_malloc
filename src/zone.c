/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaraval <tmaraval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/25 15:14:50 by tmaraval          #+#    #+#             */
/*   Updated: 2019/10/17 12:14:15 by tmaraval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

void	shrink_zone(t_zone **zone)
{
	size_t	page_sup;
	size_t	page_rm;
	int		i;

	i = 0;
	page_sup = aligne_large((*zone)->used);
	page_rm = 0;
	if (page_sup == (size_t)getpagesize() * (*zone)->pages_nbr)
		return ;
	if ((int)page_sup == getpagesize())
		return ;
	i = page_sup / getpagesize();
	while (i < (*zone)->pages_nbr)
	{
		(*zone)->state[i] = FREE;
		i++;
	}
	page_rm = (*zone)->pages_nbr - page_sup / getpagesize();
	munmap((void *)*zone + page_sup,
			getpagesize() * page_rm);
	(*zone)->pages_nbr = page_sup / getpagesize();
	(*zone)->size = page_sup - sizeof(t_zone);
	return ;
}

int		should_delete_zone(t_zone *zone)
{
	int		i;
	t_chunk *chunk;

	i = 1;
	while (i < zone->pages_nbr)
	{
		if (zone->state[i] == USED)
			return (0);
		i++;
	}
	if (zone->state[0] == USED)
	{
		chunk = zone->chunks;
		while (chunk && (void *)chunk < (void *)zone + getpagesize())
		{
			if (chunk->status != FREE)
				return (0);
			chunk = chunk->next;
		}
	}
	return (1);
}

void	delete_zone(t_zone **zone, t_zone *del, size_t size)
{
	t_zone *cpy;

	cpy = del;
	if (*zone == NULL || del == NULL)
		return ;
	if (*zone == del)
		*zone = del->next;
	if (del->next != NULL)
		del->next->prev = del->prev;
	if (del->prev != NULL)
		del->prev->next = del->next;
	debug_munmap(cpy, size);
	munmap(cpy, size);
}

/*
** Search the zone for available memory of size
** if not, add a new zone, take memory from this
** new zone and return it
*/

t_zone	*search_zone(t_zone **zone, size_t size)
{
	t_zone *tmp;
	size_t pages_nbr;

	tmp = *zone;
	pages_nbr = tmp->pages_nbr;
	while (tmp != NULL)
	{
		if (size + sizeof(t_chunk) < tmp->size - tmp->used)
			return (tmp);
		tmp = tmp->next;
	}
	if (add_zone(zone, pages_nbr) != 0)
	{
		ft_putendl_fd("malloc : error adding zone !\n", 2);
		return (NULL);
	}
	tmp = *zone;
	while (tmp->next != NULL)
		tmp = tmp->next;
	return (tmp);
}
