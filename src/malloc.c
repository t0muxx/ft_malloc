/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaraval <tmaraval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/24 15:20:19 by tmaraval          #+#    #+#             */
/*   Updated: 2019/10/15 16:49:24 by tmaraval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

pthread_mutex_t mut = PTHREAD_MUTEX_INITIALIZER;

void	*malloc_large(t_zone **zone, size_t size)
{
	t_zone *new;

	new = NULL;
	new = add_zone_large(zone, size);
	if (new == NULL)
		return (NULL);
#ifdef DEBUG_MALLOC
	ft_putstr("|DEBUG| -> END | ret from malloc_large : ");
	ft_putptr((void *)new + sizeof(t_zone));
	ft_putendl("");
#endif
	return ((void *)new + sizeof(t_zone));
}

void	*malloc_not_large(t_zone **zone, size_t size)
{
	t_zone	*zone_used;
	size_t	sz_aligned;
	void	*zone_base;
	void	*mem;

	sz_aligned = ALIGN_SIZE(size);
	if ((*zone)->chunks != NULL)
	{
		mem = search_free_chunk((*zone), sz_aligned);
		if (mem != NULL)
		{
			return (mem);
		}
	}
	zone_used = search_zone(&((*zone)), sz_aligned);
	zone_base = zone_2_mem(zone_used) + zone_used->used;
#ifdef DEBUG
	ft_putstr("|DEBUG| -> START | Request malloc size : ");
	ft_putnbr(size);
	ft_putstr(", aligned to ");
	ft_putnbr(sz_aligned);
	ft_putendl("");
#endif
	add_chunk(&(zone_used->chunks), zone_base, sz_aligned);
	zone_used->used += sz_aligned + sizeof(t_chunk);
#ifdef DEBUG_CHUNK
	print_chunks((*zone)->chunks, "chunk_");
#endif
#ifdef DEBUG
	ft_putstr("ret before malloc_not_large : ");
	ft_putptr((void *)zone_base + sizeof(t_chunk));
	ft_putendl("");
#endif
	return ((void *)zone_base + sizeof(t_chunk));
}

void	*ft_malloc(size_t size)
{
#ifdef DEBUG_MALLOC
	ft_putstr("|DEBUG| -> asked for malloc(");
	ft_putnbr((int)size);
	ft_putstr(");\n");
#endif
	if ((int)size < 0)
	{
		return (NULL);
	}
	if (size < size_max(MULTIPLE_ZONE_TINY))
	{
		if (g_malloc_state.zone_tiny == NULL)
			add_zone(&(g_malloc_state.zone_tiny), MULTIPLE_ZONE_TINY);
		return (malloc_not_large(&(g_malloc_state.zone_tiny), size));
	}
	else if (size < size_max(MULTIPLE_ZONE_MEDIUM))
	{
		if (g_malloc_state.zone_medium == NULL)
			add_zone(&(g_malloc_state.zone_medium), MULTIPLE_ZONE_MEDIUM);
		return (malloc_not_large(&(g_malloc_state.zone_medium), size));
	}
	else 
	{
		return (malloc_large(&(g_malloc_state.zone_large), size));
	}
	return (NULL);
}

void	*malloc(size_t size)
{
	void *ptr;

	pthread_mutex_lock(&mut);	
	ptr = ft_malloc(size);
#ifdef DEBUG_MALLOC
	ft_putstr("|DEBUG| -> END | ret from malloc : ");
	ft_putptr(ptr);
	ft_putendl("");
#endif
	pthread_mutex_unlock(&mut);
	return (ptr);
}
