/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaraval <tmaraval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/24 15:20:19 by tmaraval          #+#    #+#             */
/*   Updated: 2019/09/27 10:35:33 by tmaraval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"
#include "libft.h"

t_malloc g_malloc = {NULL, NULL};

int have_free_chunk(t_chunk **head)
{
	t_chunk *chunks;

	chunks = *head;
	while (chunks != NULL)
	{
		if (chunks->status == FREE)
			return (1);
	}
	return (0);
}

void remove_free_chunk(t_chunk **head)
{
	t_chunk *chunks;
	t_chunk *prev;

	chunks = *head;
	prev = *head;
	if (chunks != NULL && chunks->status == FREE)
	{
#ifdef DEBUG_FREE
	printf("|DEBUG| -> munmap chunk for size : %lu\n", chunks->size + sizeof(t_chunk));
#endif
		*head = chunks->next;
		munmap(chunks, chunks->size + sizeof(t_chunk));
		return;
	}
	while (chunks != NULL && chunks->status != FREE)
	{
		prev = chunks;
		chunks = chunks->next;
	}
	if (chunks == NULL)
		return;
	prev->next = chunks->next;
	munmap(chunks, chunks->size + sizeof(t_chunk));
}

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

void *search_chunk(t_zone *head, size_t sz_aligned)
{
	t_zone *tmp_zone;
	t_chunk *tmp_chunk;

	tmp_zone = head;
	while (tmp_zone != NULL)
	{
		tmp_chunk = tmp_zone->chunks;
		while (tmp_chunk != NULL)
		{
			if (tmp_chunk->status == FREE && tmp_chunk->size == sz_aligned)
			{
				tmp_chunk->status = USED;
				return ((void *)tmp_chunk + sizeof(t_chunk));
			}
			tmp_chunk = tmp_chunk->next;
		}
		tmp_zone = tmp_zone->next;
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
	if (g_malloc.zone_tiny->chunks != NULL)
	{
		// we have chunk allocated/freed need to search in
		mem = search_chunk(g_malloc.zone_tiny, sz_aligned);
		if (mem != NULL)
			return (mem);
	}
	zone_used = search_zone(&(g_malloc.zone_tiny), sz_aligned, g_malloc.size->sz_zone_tiny);
	zone_base = zone_2_mem(zone_used) + zone_used->used;
#ifdef DEBUG
	printf("|DEBUG| -> Request malloc size : %lu, aligned to %lu\n", size, sz_aligned);
#endif
	add_chunk(&(zone_used->chunks), zone_base, sz_aligned);
	zone_used->used += sz_aligned + sizeof(t_chunk);
#ifdef DEBUG_ZONE
	printf("|DEBUG| -> current zone used : %lu\n", g_malloc.zone_tiny->used);
#endif
#ifdef DEBUG_CHUNK
	printf("|DEBUG| -> added new chunk g_malloc.zone_tiny->used : %lu\n", g_malloc.zone_tiny->used);
	print_chunks(g_malloc.zone_tiny->chunks, "chunk_tiny");
#endif

	return ((void *)zone_base + sizeof(t_chunk));
}

void *ft_malloc(size_t size)
{
	if ((int)size < 0)
	{
		return NULL;
	}
	if (init_malloc() != 0)
	{
		// manage error
	}
	if (size < g_malloc.size->sz_tiny)
	{
		return(malloc_tiny(size));
	}
	return (NULL);
}
