/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaraval <tmaraval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/25 11:30:28 by tmaraval          #+#    #+#             */
/*   Updated: 2019/09/27 10:53:20 by tmaraval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

void munmap_small_medium(t_zone **zone, size_t size_min)
{
	t_zone *tmp_zone;
	t_zone *prev_zone;
	t_chunk *tmp_chunk;

	tmp_zone = *zone;
	prev_zone = *zone;
	while (tmp_zone != NULL)
	{
		// We used more then the half of the zone size
		// let's check if we can munmap freed chunk
		if (tmp_zone->used > tmp_zone->size / 2)
		{
			tmp_chunk = tmp_zone->chunks;
			while (have_free_chunk(&tmp_chunk) != 0)
				remove_free_chunk(&tmp_chunk);
		}
		tmp_zone = tmp_zone->next;
	}
	while (zone_need_free(zone, size_min) != 0)
		remove_zone(zone, size_min);
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
		munmap_small_medium(&(g_malloc.zone_tiny), g_malloc.size->sz_min_alloc_tiny);
			
	}
#ifdef DEBUG_FREE
	printf("|DEBUG| -> after free\n");
	print_chunks(g_malloc.chunk_tiny, "chunk_tiny");
#endif
}
