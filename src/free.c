/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaraval <tmaraval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/25 11:30:28 by tmaraval          #+#    #+#             */
/*   Updated: 2019/10/01 15:10:46 by tmaraval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"


void munmap_small_medium(t_zone **zones)
{
	t_zone *zone;

	zone = *zones;
	while (zone != NULL)
	{
		page_free(&zone, zone->pages_nbr);	
		zone = zone->next;
	}
}

void ft_free(void *ptr)
{
	t_chunk *chunk;

#ifdef DEBUG_FREE
	printf("|DEBUG| -> before free\n");
	print_chunks(g_malloc.chunk_tiny, "chunk_tiny");
#endif
	chunk = ptr - sizeof(t_chunk);
	if (chunk->size < g_malloc.size->sz_tiny)
	{
		chunk->status = FREE;
		munmap_small_medium(&(g_malloc.zone_tiny));
			
	}
#ifdef DEBUG_FREE
	printf("|DEBUG| -> after free\n");
	print_chunks(g_malloc.chunk_tiny, "chunk_tiny");
#endif
}
