/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaraval <tmaraval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/24 15:20:19 by tmaraval          #+#    #+#             */
/*   Updated: 2019/10/03 13:01:28 by tmaraval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

void	*malloc_not_large(t_zone **zone, size_t size)
{
	t_zone	*zone_used;
	size_t	sz_aligned;
	void	*zone_base;
	void	*mem;

	ft_putstr("asked for malloc(");
	ft_putnbr(size);
	ft_putstr(");\n");
	sz_aligned = ALIGN_SIZE(size);
	if ((*zone)->chunks != NULL)
	{
		mem = search_chunk((*zone), sz_aligned);
		if (mem != NULL)
			return (mem);
	}
	zone_used = search_zone(&((*zone)), sz_aligned);
	zone_base = zone_2_mem(zone_used) + zone_used->used;
#ifdef DEBUG
	ft_putstr("|DEBUG| -> Request malloc size : ");
	ft_putnbr(size);
	ft_putstr(", aligned to ");
	ft_putnbr(sz_aligned);
	ft_putendl("");
#endif
	add_chunk(&(zone_used->chunks), zone_base, sz_aligned);
	zone_used->used += sz_aligned + sizeof(t_chunk);
#ifdef DEBUG_CHUNK
	print_chunks((*zone)->chunks, "chunk_tiny");
#endif
	return ((void *)zone_base + sizeof(t_chunk));
}

void	*ft_malloc(size_t size)
{
	if ((int)size < 0)
	{
		return (NULL);
	}
	if (init_malloc() != 0)
	{
		return (NULL);
	}
	if (size < size_max(MULTIPLE_ZONE_TINY))
	{
		return (malloc_not_large(&(g_malloc_state.zone_medium), size));
	}
	if (size < size_max(MULTIPLE_ZONE_MEDIUM))
	{
		return (malloc_not_large(&(g_malloc_state.zone_medium), size));
	}
	return (NULL);
}

void	*malloc(size_t size)
{
	void *ptr;

	ptr = ft_malloc(size);
#ifdef DEBUG
	ft_putstr("ret from malloc : ");
	ft_putptr(ptr);
	ft_putendl("");
#endif
	return (ptr);
}

void	free(void *ptr)
{
	ft_free(ptr);
}
