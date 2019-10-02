/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaraval <tmaraval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/25 15:14:50 by tmaraval          #+#    #+#             */
/*   Updated: 2019/10/02 14:48:36 by tmaraval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

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
	printf("|DEBUG| -> need to add new zone !\n");
#endif
	if (add_zone(zone, pages_nbr) != 0)
	{
		ft_putendl_fd("malloc : error adding zone !\n", 2);
		return (NULL);
	}
	tmp = *zone;
	while (tmp->next != NULL)
		tmp = tmp->next;
#ifdef DEBUG_ZONE
	printf("RET FROM HERE %p\n", tmp);
#endif
	return (tmp);
}

/*
** Add new zone, the 0x1000 here is for the t_zone struct
*/

int		add_zone(t_zone **zone, size_t pages_nbr)
{
	t_zone *head;
	t_zone *new;
//	void 	*mem;
	size_t 	size;

	new = NULL;
	size = 0x1000 * pages_nbr;
	// mmap memory for the new zone
	new = mmap(0, size + 0x1000, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
	if (new == MAP_FAILED) 
	{
		ft_putendl_fd("malloc : can't mmap memory for zone_tiny", 2);
		return (-1);
	}
//	new = (t_zone *)mem;
	ft_memset(new, 0, size + 0x1000);
	new->size = size;
	new->used = 0;
	new->next = NULL;
	new->pages_nbr = pages_nbr;
	ft_memset(new->state, USED, MULTIPLE_ZONE_TINY);
	new->chunks = NULL;
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
