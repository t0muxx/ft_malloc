/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaraval <tmaraval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/25 15:14:50 by tmaraval          #+#    #+#             */
/*   Updated: 2019/10/10 15:00:57 by tmaraval         ###   ########.fr       */
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
#ifdef DEBUG_MUNMAP
	ft_putstr("zone_shrink - munmaped : ");
	ft_putnbr(getpagesize() * page_rm);
	ft_putendl("");
#endif
	munmap((void *)*zone + page_sup,
			getpagesize() * page_rm);
	(*zone)->pages_nbr = page_sup / getpagesize();
	(*zone)->size = page_sup - sizeof(t_zone);
	return ;
	
}

int		should_delete_zone(t_zone *zone)
{
	int i;
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
#ifdef DEBUG_ZONE
	ft_putstr("delete zone : ");
	ft_putptr(del);
	ft_putstr(" size = : ");
	ft_putnbr(del->size);
	ft_putendl("");
	print_zones(*zone, "ZONOE BEFORE REMOVE");
	ft_putstr("|DEBUG| -> deleting zone : ");
	ft_putptr(del);
	ft_putendl("");
#endif
	if (*zone == NULL || del == NULL)
		return ;
	if (*zone == del)
		*zone = del->next;
	if (del->next != NULL)
		del->next->prev = del->prev;
	if (del->prev != NULL)
		del->prev->next = del->next;
#ifdef DEBUG_MUNMAP
	ft_putstr("munmaped size :");
	ft_putnbr(size);
	ft_putendl(");");
#endif
	munmap(cpy, size);
#ifdef DEBUG_ZONE
	print_zones(*zone, "ZONOE AFTER REMOVE");
#endif
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
#ifdef DEBUG_ZONE
	ft_putendl("|DEBUG| -> need to add new zone !");
#endif
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

t_zone		*add_zone_large(t_zone **zone, size_t size)
{
	t_zone *head;
	t_zone *new;
	size_t aligned;

	new = NULL;
	aligned = aligne_large(size + sizeof(t_zone));
	new = mmap(0, aligned,
		PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
#ifdef DEBUG_MMAP
	ft_putstr("mmaped size : ");
	ft_putnbr(aligned);
	ft_putendl("");
#endif
	if (new == MAP_FAILED)
	{
		ft_putendl_fd("malloc : can't mmap memory for zone_tiny", 2);
		return (NULL);
	}
	ft_memset(new, 0, aligned);
	new->size = size;
	new->used = 0;
	new->next = NULL;
	new->pages_nbr = 0;
	new->chunks = NULL;
	head = *zone;
	if (*zone == NULL)
		*zone = new;
	else
	{
		while (head->next != NULL)
			head = head->next;
		head->next = new;
		new->prev = head;
	}
#ifdef DEBUG_ZONE
	print_zones(*zone, "zones_larges :");
#endif
	return (new);
}

/*
** Add new zone, the 0x1000 here is for the t_zone struct
*/

int		add_zone(t_zone **zone, size_t pages_nbr)
{
	t_zone	*head;
	t_zone	*new;
	size_t	size;

	new = NULL;
	size = getpagesize() * pages_nbr;
	new = mmap(0, size,
			PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
#ifdef DEBUG_MMAP
	ft_putstr("mmaped size : ");
	ft_putnbr(size);
	ft_putendl("");
#endif
	if (new == MAP_FAILED)
	{
		ft_putendl_fd("malloc : can't mmap memory for zone_tiny", 2);
		return (-1);
	}
	ft_memset(new, 0, size);
	new->size = size - sizeof(t_zone);
	new->used = 0;
	new->next = NULL;
	new->prev = NULL;
	new->pages_nbr = pages_nbr;
	ft_memset(new->state, USED, pages_nbr);
	new->chunks = NULL;
	head = *zone;
	if (*zone == NULL)
		*zone = new;
	else
	{
		while (head->next != NULL)
			head = head->next;
		head->next = new;
		new->prev = head;
	}
#ifdef DEBUG_ZONE
	print_zones(*zone, "zones :");
#endif
	return (0);
}
