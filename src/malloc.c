/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaraval <tmaraval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/24 15:20:19 by tmaraval          #+#    #+#             */
/*   Updated: 2019/10/02 14:56:11 by tmaraval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

void *malloc_tiny(size_t size)
{
	t_zone *zone_used;
	size_t sz_aligned;
	void *zone_base;
	void *mem;

	sz_aligned = ALIGN_SIZE(size);
	if (g_malloc_state.zone_tiny->chunks != NULL)
	{
		// we have chunk allocated/freed need to search in
		mem = search_chunk(g_malloc_state.zone_tiny, sz_aligned);
		if (mem != NULL)
			return (mem);
	}
	zone_used = search_zone(&(g_malloc_state.zone_tiny), sz_aligned);
	zone_base = zone_2_mem(zone_used) + zone_used->used;
#ifdef DEBUG
	printf("|DEBUG| -> Request malloc size : %lu, aligned to %lu\n", size, sz_aligned);
#endif
	add_chunk(&(zone_used->chunks), zone_base, sz_aligned);
	zone_used->used += sz_aligned + sizeof(t_chunk);
#ifdef DEBUG_ZONE
	printf("|DEBUG| -> current zone used : %lu\n", g_malloc_state.zone_tiny->used);
#endif
#ifdef DEBUG_CHUNK
	printf("|DEBUG| -> added new chunk g_malloc_state.zone_tiny->used : %lu\n", g_malloc_state.zone_tiny->used);
	print_chunks(g_malloc_state.zone_tiny->chunks, "chunk_tiny");
	printf("############################### -> |%p|\n", (void *)zone_base + sizeof(t_chunk));
	printf("############################### -> ALIGNED ? : |%d|\n", ((long)(void *)zone_base + sizeof(t_chunk))%16 == 0);
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
		return (NULL);
	}
	if (size < size_max(MULTIPLE_ZONE_TINY))
	{
		return(malloc_tiny(size));
	}
	return (NULL);
}

void *malloc(size_t size)
{
	return (ft_malloc(size));
}

void free(void *ptr)
{
	ft_free(ptr);
}
