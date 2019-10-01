/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaraval <tmaraval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/25 11:30:28 by tmaraval          #+#    #+#             */
/*   Updated: 2019/10/01 11:46:28 by tmaraval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"


int zone_page_free_check_chunk_state_for_page(t_chunk **chunk, void *base, int p)
{
	int need_remove;

	need_remove = 0;
	while (*chunk != NULL &&
	((void *)*chunk >= base + (getpagesize() * p)))
	{
		if ((*chunk)->status != FREE)
			return (0);
		else
			need_remove = 1;
		*chunk = (*chunk)->prev;
	}
	return (need_remove);
}

t_chunk *zone_page_free_find_chunk_left_border(t_chunk **chunk, void *base, int p)
{
	t_chunk *ret;
	t_chunk *prev;

	prev = NULL;
	ret = NULL;
	while (chunk != NULL
	&& (void *)*chunk < base + (getpagesize() * (p + 1)))
	{
		printf("chunk->next : %p\n", (*chunk)->next);
		prev = *chunk;
		*chunk = (*chunk)->next;
	}
	ret = *chunk;
	*chunk = prev;
	return ret;
}

/*
**       0x0 +-----------------------------------------------------------+
**          |                                                           |
**          |               T_ZONE                                      |
**          |                                                           |
**          |                                                           |
**(base)0x1000 +----------+-----------------------------------+---------+
**          |    USED     |          USED                     |         |
**          |             |                                   | FREE ....     p = 0
**          |             |                                   |         |
**          |             |                                   |         |
** 0x2000   +--------+----+--------------------+--------------+---------+
**          |.....   |                         |                        |
**          |        |   FREE                  |    FREE.................
**          |        |                         |                        |       p = 1
**          |        |                         |                        |
** 0x3000   +--------+---+chunk_after----------+---------------+--------+
**          ..........   |                                     |        |
**          |            |   USED                              |   USED |     p = 2
**          |            |                                     |        |
**0x4000    +------------+----------+--------------------------+--------+
**          |                       |                                   |
**          |      USED             |                                   |      p = 3
**          +-----------------------+-----------------------------------+
**
** With a zone with this layout,
** zone_page_free will iterate the chunks for each page until it arrive to
** the first chunk in p + 1, and it will backward in chunks until it arrive 
** to the last chunk of p - 1.
** if all thoses chunks are free, we can munmap the memory for p.
*/

void zone_page_free(t_zone **current_zone, size_t pages_nbr)
{
	int p;
	t_chunk *chunk;
	t_chunk *chunk_after;
	void *base;
	int need_remove;
	t_chunk *cpy;

	need_remove = 0;
	base = zone_2_mem(*current_zone);
	p = 0;
	chunk = (*current_zone)->chunks;
	print_chunks(chunk, "ICI : ");
	while ((size_t)p < pages_nbr)
	{
		chunk = (*current_zone)->chunks;
		printf("page = %d\n", p);
		if ((*current_zone)->state[p] != FREE)
		{
			chunk_after = zone_page_free_find_chunk_left_border(&chunk, base, p);
			
			while (chunk != NULL &&
					((void *)chunk >= base + (getpagesize() * p)))
			{
				if (chunk->status != FREE)
				{
					need_remove = 0;
					break;
				}
				else
					need_remove = 1;
				chunk = chunk->prev;
			}
			//need_remove = zone_page_free_check_chunk_state_for_page(&chunk, base, p);
			if (chunk_after == NULL)
				break ;
			chunk = chunk_after->prev;
			if (need_remove == 1)
			{
				while (chunk != NULL &&
						((void *)chunk >= base + (getpagesize() * p)))
				{
					printf("deleted chunk : %p\n", chunk);
					cpy = chunk->prev;
					printf("cpy = %p\n", cpy);
					delete_chunk(&((*current_zone)->chunks), chunk);
					chunk = cpy;
					printf("chunk now : %p\n", chunk);
					printf("((void *)chunk > base + (getpagesize() * p)) = %p\n", (void *)( base + (getpagesize() * p)));
				}
					munmap(base + getpagesize() * p, getpagesize());
					(*current_zone)->state[p] = FREE;
			}
			print_chunks((*current_zone)->chunks, "############## AFTER REMOVE ########");
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
