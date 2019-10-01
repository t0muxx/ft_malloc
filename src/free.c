/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaraval <tmaraval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/25 11:30:28 by tmaraval          #+#    #+#             */
/*   Updated: 2019/09/30 15:48:20 by tmaraval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

/*
       0x0 +-----------------------------------------------------------+
          |                                                           |
          |               T_ZONE                                      |
          |                                                           |
          |                                                           |
          |                                                           |
(base)0x1000 +----------+-----------------------------------+---------+
          |    USED     |          USED                     |         |
          |             |                                   | FREE ....     p = 0
          |             |                                   |         |
          |             |                                   |         |
 0x2000   +--------+----+--------------------+--------------+---------+
          |.....   |                         |                        |
          |        |   FREE                  |    FREE.................
          |        |                         |                        |       p = 1
          |        |                         |                        |
 0x3000   +--------+---+chunk_after----------+---------------+--------+
          ..........   |                                     |        |
          |            |   USED                              |   USED |     p = 2
          |            |                                     |        |
0x4000    +------------+----------+--------------------------+--------+
          |                       |                                   |
          |      USED             |                                   |      p = 3
          +-----------------------+-----------------------------------+

With a zone with this layout,
zone_page_free will iterate the chunks for each page until it arrive to
the first chunk in p + 1, and it will backward in chunks until it arrive 
to the last chunk of p - 1.
if all thoses chunks are free, we can munmap the memory for p.
*/

void zone_page_free(t_zone **current_zone, size_t pages_nbr)
{
	int p;
	t_chunk *chunk;
	t_chunk *chunk_after;
	void *base;

	base = zone_2_mem(*current_zone);
	p = 0;
	chunk = (*current_zone)->chunks;
	while ((size_t)p < pages_nbr)
	{
		if ((*current_zone)->state[p] != FREE)
		{
			while (chunk != NULL &&
				   (void *)chunk < base + (getpagesize() * (p + 1)))
				chunk = chunk->next;	
			chunk_after = chunk;
			while (chunk != NULL &&
					((void *)chunk > base + (getpagesize() * p)))
			{
				if (chunk->status != FREE)
					break;
				chunk_after->prev = chunk;
				chunk->next = chunk_after;
				munmap(base + getpagesize() * p, getpagesize());
				(*current_zone)->state[p] = FREE;
			}
		}
		p++;
	}
}

void munmap_small_medium(t_zone **zones)
{
	t_zone *zone;

	zone = *zones;
	while (zone != NULL)
	{
		zone_page_free(&zone, zone->pages_nbr);	
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
