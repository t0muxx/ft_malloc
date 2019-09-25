/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaraval <tmaraval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/24 15:20:19 by tmaraval          #+#    #+#             */
/*   Updated: 2019/09/25 16:13:03 by tmaraval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"
#include "libft.h"

t_malloc g_malloc = {NULL, NULL};

void add_chunk(t_chunk **head, void *zone_base, size_t sz_aligned)
{
	t_chunk *tmp;
	t_chunk *new;

	new = zone_base;
	new->status = USED;
    new->size = sz_aligned;
	new->prev = NULL;
	new->next = NULL;
	tmp = *head;
	if (*head == NULL)
		*head = new;
	else
	{
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = new;
	}
}

void *search_chunk(t_chunk *head, size_t sz_aligned)
{
	t_chunk *tmp;

	tmp = head;
	while (tmp != NULL)
	{
		if (tmp->status == FREE && tmp->size == sz_aligned)
		{
			tmp->status = USED;
			return ((void *)tmp + sizeof(t_chunk));
		}
		tmp = tmp->next;
	}
	return (NULL);
}

void *malloc_tiny(size_t size)
{
	t_zone *zone_used;
	size_t sz_aligned;
	void *zone_base;
	void *mem;

	sz_aligned = ALIGN_SIZE(size);
	if (g_malloc.chunk_tiny != NULL)
	{
		// we have chunk allocated/freed need to search in
		mem = search_chunk(g_malloc.chunk_tiny, sz_aligned);
		if (mem != NULL)
			return (mem);
	}
	zone_used = search_zone(&(g_malloc.zone_tiny), sz_aligned, SZ_ZONE_TINY);
	zone_base = zone_2_mem(zone_used) + zone_used->used;
#ifdef DEBUG
	printf("|DEBUG| -> Request malloc size : %lu, aligned to %lu\n", size, sz_aligned);
#endif
	add_chunk(&(g_malloc.chunk_tiny), zone_base, sz_aligned);
	zone_used->used += sz_aligned + sizeof(t_chunk);
#ifdef DEBUG_ZONE
	printf("|DEBUG| -> current zone used : %lu\n", g_malloc.zone_tiny->used);
#endif
#ifdef DEBUG_CHUNK
	printf("|DEBUG| -> added new chunk g_malloc.zone_tiny->used : %lu\n", g_malloc.zone_tiny->used);
	printf("|DEBUG| -> addr of the chunk mem : %p\n", (void *)g_malloc.chunk_tiny + sizeof(t_chunk));
	print_chunks(g_malloc.chunk_tiny, "chunk_tiny");
#endif

	return ((void *)zone_base + sizeof(t_chunk));
}

void *ft_malloc(size_t size)
{
	if (size < 0)
	{
		return NULL;
	}
	if (init_malloc(&g_malloc) != 0)
	{
		// manage error
	}
	if (size < SZ_TINY)
	{
		return(malloc_tiny(size));
	}
	return (NULL);
}
