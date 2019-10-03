/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaraval <tmaraval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/25 11:30:28 by tmaraval          #+#    #+#             */
/*   Updated: 2019/10/03 12:59:08 by tmaraval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

void	munmap_small_medium(t_zone **zones)
{
	t_zone *zone;

	zone = *zones;
	if (cnt_zone(zone) == 1)
		return ;
	while (zone != NULL)
	{
		page_free(&zone, zone->pages_nbr);
		zone = zone->next;
	}
}

void	ft_free(void *ptr)
{
	t_chunk *chunk;

#ifdef DEBUG_FREE
	ft_putendl("|DEBUG| -> before free");
	print_chunks(g_malloc_state.zone_tiny->chunks, "chunk_tiny");
#endif
	chunk = ptr - sizeof(t_chunk);
	if (chunk->size < size_max(MULTIPLE_ZONE_TINY))
	{
		chunk->status = FREE;
		munmap_small_medium(&(g_malloc_state.zone_tiny));
	}
#ifdef DEBUG_FREE
	ft_putendl("|DEBUG| -> after free");
	print_chunks(g_malloc_state.zone_tiny->chunks, "chunk_tiny");
#endif
}
