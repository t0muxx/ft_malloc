/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaraval <tmaraval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/25 15:14:50 by tmaraval          #+#    #+#             */
/*   Updated: 2019/09/27 10:48:05 by tmaraval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

int  zone_need_free(t_zone **zone, size_t size_alloc_min)
{
	t_zone *tmp;

	tmp = *zone;
	while (tmp != NULL)
	{
		if (tmp->size - tmp->used < size_alloc_min + sizeof(t_chunk) && tmp->chunks == NULL)
			return (1);
	}
	return (0);
}

void remove_zone(t_zone **zone, size_t size_alloc_min)
{
	t_zone *tmp;
	t_zone *prev;
	
	tmp = *zone;
	prev = *zone;
	if (tmp != NULL && tmp->size - tmp->used < size_alloc_min + sizeof(t_chunk) && tmp->chunks == NULL)
	{
		*zone = tmp->next;
		munmap(tmp + tmp->used, tmp->size - tmp->used);
		munmap(tmp, sizeof(t_zone));
		return ;
	}
	while (tmp != NULL && tmp->size - tmp->used < size_alloc_min + sizeof(t_chunk) && tmp->chunks == NULL)
	{
		prev = tmp;
		tmp = tmp->next;
	}
	if (tmp == NULL)
		return;
	prev->next = tmp->next;
	munmap(tmp + tmp->used, tmp->size - tmp->used);
	munmap(tmp, sizeof(t_zone));
}

// Search the zone for available memory of size
// if not, add a new zone, take memory from this
// new zone and return it
void  *search_zone(t_zone **zone, size_t size, size_t sz_zone)
{
	t_zone *tmp;

	tmp = *zone;
	while (tmp != NULL)
	{
		if (size + sizeof(t_chunk) < tmp->size - tmp->used)
			return (tmp);
		tmp = tmp->next;
	}
#ifdef DEBUG_ZONE
	printf("|DEBUG| -> need to add new zone !\n");
#endif
	if (add_zone(zone, sz_zone) != 0)
	{
		ft_putendl_fd("malloc : error adding zone !\n", 2);
		return (NULL);
	}
	tmp = *zone;
	while (tmp->next != NULL)
		tmp = tmp->next;
	return (tmp);
}

int add_zone(t_zone **zone, size_t size)
{
	t_zone *head;
	t_zone *new;
	void *mem;

	// mmap memory for the new zone
	mem = mmap(0, sizeof(t_zone) + size, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0);
#ifdef DEBUG
	printf("|DEBUG| -> mmaped zone_tiny : %lu\n", g_malloc.size->sz_zone_tiny);
#endif
	if (mem == MAP_FAILED) 
	{
		ft_putendl_fd("malloc : can't mmap memory for zone_tiny", 2);
		return (-1);
	}
	new = mem;
	new->size = size;
	new->used = 0;
	new->next = NULL;
	new->chunks = NULL;
	ft_memset(zone_2_mem(new), 0, size);
	head = *zone;
	if (*zone == NULL)
		*zone = new;
	else
	{
		while (head->next != NULL)
			head = head->next;
		head->next = new;
	}
#ifdef DEBUG_ZONE
	print_zones(*zone, "zones :");
#endif
	return (0);
}
