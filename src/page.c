/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   page.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaraval <tmaraval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/01 15:07:40 by tmaraval          #+#    #+#             */
/*   Updated: 2019/10/01 16:43:45 by tmaraval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

/*
** zone_page_free_remove_chunk_and_munmap will
** iterate backward the chunks for page p and
** will remove them from the linked list
** and munmap the corresponding page
*/

void page_free_remove_chunk_and_munmap(
		t_zone **current_zone, t_chunk **chunk, void *base, int p)
{
	t_chunk *cpy;
	
	cpy = NULL;
	while (*chunk != NULL &&
	((void *)*chunk >= base + (getpagesize() * p)))
	{
#ifdef DEBUG_PAGE
		printf("deleted chunk : %p\n", *chunk);
#endif
		cpy = (*chunk)->prev;
		delete_chunk(&((*current_zone)->chunks), *chunk);
		*chunk = cpy;
	}
	if (*chunk != NULL)
	{
		cpy = (*chunk)->prev;
		delete_chunk(&((*current_zone)->chunks), *chunk);
		*chunk = cpy;
	}
#ifdef DEBUG_PAGE
		printf("deleted chunk : %p\n", *chunk);
#endif
	munmap(base + getpagesize() * p, getpagesize());
#ifdef DEBUG_PAGE
		printf("munmaped page num : %d\n", p);
#endif
	(*current_zone)->state[p] = FREE;
}

/*
** zone_page_free_check_chunk_state_for_page will chunk
** the state of chunks before chunk for the current explored
** page and will return 1 if all the chunks are free
*/

int page_free_check_chunk_state_for_page(t_chunk **chunk, void *base, int p)
{
	int need_remove;

	need_remove = 0;
	while (*chunk != NULL &&
	((void *)*chunk >= base + (getpagesize() * p)))
	{
		printf("checking chunk : %p\n", *chunk);
		if ((*chunk)->status != FREE)
			return (0);
		else
			need_remove = 1;
		*chunk = (*chunk)->prev;
	}
	if (*chunk != NULL && (*chunk)->status != FREE)
		need_remove = 0;
	return (need_remove);
}

/*
** zone_page_free_find_chunk_left_border will check
** the next chunks after chunk for the current page explored
** and will stop and return the first chunk for page p
*/

t_chunk *page_free_find_chunk_left_border(t_chunk **chunk, void *base, int p)
{
	t_chunk *ret;
	t_chunk *prev;

	prev = NULL;
	ret = NULL;
	while (*chunk != NULL
	&& (void *)*chunk < base + (getpagesize() * (p + 1)))
	{
#ifdef DEBUG_PAGE
	if (*chunk != NULL
	&& (void *)*chunk >= base + (getpagesize() * p) 
	&& (void *)*chunk <= base + (getpagesize() * (p + 1)))
		print_chunk(*chunk);
#endif
		prev = *chunk;
		*chunk = (*chunk)->next;
	}
	ret = *chunk;
	*chunk = prev;
	return ret;
}

/*
** zone_page_free_check_chunk will check
** if all chunks for a given page are free
** and if yes will remove them and munmap
** the coressponding page
*/

void page_free_check_chunk(t_zone **current_zone, t_chunk **chunk,
		void *base, int p)
{
	t_chunk *chunk_after;
	int need_remove;

	need_remove = 0;
	*chunk = (*current_zone)->chunks;
#ifdef DEBUG_PAGE	
	printf("page = %d\n", p);
#endif
	if ((*current_zone)->state[p] != FREE)
	{
		chunk_after = page_free_find_chunk_left_border(chunk, base, p);
#ifdef DEBUG_PAGE	
		printf("left_border: %p\n", chunk_after);
		printf("chunk for check state : %p\n", *chunk);
#endif
		need_remove = page_free_check_chunk_state_for_page(chunk, base, p);
		if (chunk_after == NULL)
			return ;
		*chunk = chunk_after->prev;
		if (need_remove == 1)
		{
			page_free_remove_chunk_and_munmap(
					current_zone, chunk, base, p);
#ifdef DEBUG_PAGE	
		print_chunks((*current_zone)->chunks, "############## AFTER REMOVE ########");
#endif
		}
	}
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

void page_free(t_zone **current_zone, size_t pages_nbr)
{
	int p;
	t_chunk *chunk;
	void *base;

	base = zone_2_mem(*current_zone);
	p = 0;
	chunk = (*current_zone)->chunks;
#ifdef DEBUG_PAGE	
	print_chunks(chunk, "ICI : ");
#endif
	while ((size_t)p < pages_nbr)
	{
		page_free_check_chunk(current_zone, &chunk, base, p);
		p++;
	}
}
