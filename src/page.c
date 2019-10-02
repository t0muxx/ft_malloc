/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   page.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaraval <tmaraval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/01 15:07:40 by tmaraval          #+#    #+#             */
/*   Updated: 2019/10/02 09:29:29 by tmaraval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"


t_chunk *page_free_find_chunk_left_border(t_chunk *left_border, void *base, int p)
{
	t_chunk *chunk;

	chunk = left_border;
	while (chunk != NULL 
	&& (void *)chunk >= base + (getpagesize() * p) )
		chunk = chunk->prev;
	return (chunk);
}

t_chunk *page_free_find_chunk_right_border(t_chunk *chunk_head, void *base, int p)
{
	t_chunk *chunk;

	chunk = chunk_head;
	while (chunk->next != NULL
	&& (void *)chunk->next < base + (getpagesize() * (p + 1)))
	{
#ifdef DEBUG_PAGE
	if (chunk != NULL
	&& (void *)chunk >= base + (getpagesize() * p) 
	&& (void *)chunk <= base + (getpagesize() * (p + 1)))
		print_chunk(chunk);
#endif
		chunk = chunk->next;
	}
	return chunk;
}

void page_free_remove_chunks(t_chunk **head, t_chunk *right_border, t_chunk *left_border)
{
	t_chunk *chunk;
	t_chunk *tmp;

	chunk = right_border;
	while (chunk != left_border)
	{
#ifdef DEBUG_PAGE
		printf("removed chunk\n");
		print_chunk(chunk);
#endif
		tmp = chunk->prev;
		delete_chunk(head, chunk);
		chunk = tmp;
	}
	if (chunk != NULL && chunk->status == FREE)
	{
#ifdef DEBUG_PAGE
		printf("removed chunk\n");
		print_chunk(chunk);
#endif
		delete_chunk(head, chunk);
	}
}

int page_free_shall_remove_page(t_chunk *right_border, t_chunk *left_border, void *base, int p)
{
	t_chunk *chunk;

	chunk = right_border;
	while (chunk != left_border)
	{
		if (chunk->status != FREE)
			return (0);
		chunk = chunk->prev;
	}
	if (chunk == NULL || (void *)chunk == base + (getpagesize() * (p)))
		return (1);
	else if (chunk != NULL && chunk->status == FREE)
		return (1);
	return (0);
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
	t_chunk *left_border;
	t_chunk *right_border;

	*chunk = (*current_zone)->chunks;
#ifdef DEBUG_PAGE	
	printf("page = %d\n", p);
#endif
	if ((*current_zone)->state[p] != FREE)
	{
		right_border = page_free_find_chunk_right_border(*chunk, base, p);
		if (!((void *)right_border < base + (getpagesize() * (p))))
		{
#ifdef DEBUG_PAGE	
			printf("right_border: %p\n", right_border);
#endif
			left_border = page_free_find_chunk_left_border(right_border, base, p);
#ifdef DEBUG_PAGE	
			printf("left_border: %p\n", left_border);
#endif
			if (page_free_shall_remove_page(right_border, left_border, base, p) == 1)
			{
				printf("shall remove page : %d\n", p);
				page_free_remove_chunks(&((*current_zone)->chunks), right_border, left_border);
				(*current_zone)->state[p] = FREE;
				munmap(base + getpagesize() * p, getpagesize());
#ifdef DEBUG_PAGE
				printf("munmaped page num : %d\n", p);
				print_chunks((*current_zone)->chunks, "############## AFTER REMOVE ########");
#endif
			}
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