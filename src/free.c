/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaraval <tmaraval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/25 11:30:28 by tmaraval          #+#    #+#             */
/*   Updated: 2019/10/11 13:55:49 by tmaraval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

void	munmap_large(t_zone **zone, void *ptr)
{
	t_zone *del;

	del = ptr - sizeof(t_zone);
	delete_zone(zone, del, aligne_large(del->size + sizeof(t_zone)));
}

void	munmap_small_medium(t_zone **zones)
{
	t_zone *zone;

	zone = *zones;
	if (cnt_zone(zone) == 1)
		return ;
	while (zone != NULL)
	{
		page_free(&zone);
		if (should_delete_zone(zone))
		{
			delete_zone(zones, zone, getpagesize());
			zone = *zones;
		}
		else	
			zone = zone->next;
	}
}

void	ft_free(void *ptr)
{
	t_chunk *chunk;

	if (ptr == NULL)
		return ;
	if (search_chunk(&(g_malloc_state.zone_tiny), ptr) == 1)
	{
		chunk = ptr - sizeof(t_chunk);
		chunk->status = FREE;
		munmap_small_medium(&(g_malloc_state.zone_tiny));
	}
	else if (search_chunk(&(g_malloc_state.zone_medium), ptr) == 1)
	{
		chunk = ptr - sizeof(t_chunk);
		chunk->status = FREE;
		munmap_small_medium(&(g_malloc_state.zone_medium));
	}
	else if (search_chunk_large(&g_malloc_state.zone_large, ptr) == 1)
	{
		munmap_large(&g_malloc_state.zone_large, ptr);
	}
	else
		;
	debug_all(&g_malloc_state);
	return ;


#ifdef DEBUG_FREE
	ft_putendl("|DEBUG| -> before free");
	print_chunks(g_malloc_state.zone_tiny->chunks, "chunk_tiny");
#endif
#ifdef DEBUG_FREE
	ft_putendl("|DEBUG| -> after free");
	print_chunks(g_malloc_state.zone_tiny->chunks, "chunk_tiny");
#endif
}
