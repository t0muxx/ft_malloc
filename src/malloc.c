/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaraval <tmaraval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/24 15:20:19 by tmaraval          #+#    #+#             */
/*   Updated: 2019/10/17 12:07:29 by tmaraval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

pthread_mutex_t g_mut = PTHREAD_MUTEX_INITIALIZER;
t_malloc		g_malloc_state = {NULL, NULL, NULL, 0};

void	*malloc_large(t_zone **zone, size_t size)
{
	t_zone *new;

	new = NULL;
	new = add_zone_large(zone, size);
	if (new == NULL)
		return (NULL);
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
	add_chunk(&(zone_used->chunks), zone_base, sz_aligned);
	zone_used->used += sz_aligned + sizeof(t_chunk);
	return ((void *)zone_base + sizeof(t_chunk));
}

void	*ft_malloc(size_t size)
{
	if ((int)size < 0)
		return (NULL);
	if (size < size_max(MULTIPLE_ZONE_TINY))
	{
		if (g_malloc_state.zone_tiny == NULL)
		{
			if ((add_zone(&(g_malloc_state.zone_tiny), MULTIPLE_ZONE_TINY)) < 0)
				return (NULL);
		}
		return (malloc_not_large(&(g_malloc_state.zone_tiny), size));
	}
	else if (size < size_max(MULTIPLE_ZONE_MEDIUM))
	{
		if (g_malloc_state.zone_medium == NULL)
		{
			if ((add_zone(&(g_malloc_state.zone_medium),
							MULTIPLE_ZONE_MEDIUM)) < 0)
				return (NULL);
		}
		return (malloc_not_large(&(g_malloc_state.zone_medium), size));
	}
	else
		return (malloc_large(&(g_malloc_state.zone_large), size));
	return (NULL);
}

void	*malloc(size_t size)
{
	void *ptr;

	if (g_malloc_state.opt == 0)
		init_opt(&(g_malloc_state.opt));
	if (g_malloc_state.opt & DEBUG_MALLOC)
	{
		ft_putstr("|DEBUG| -> malloc(");
		ft_putnbr(size);
		ft_putendl(");");
	}
	pthread_mutex_lock(&g_mut);
	ptr = ft_malloc(size);
	if (g_malloc_state.opt & DEBUG_MALLOC_RET)
	{
		ft_putstr("|DEBUG| -> ret from malloc : ");
		ft_putptr(ptr);
		ft_putendl("");
	}
	pthread_mutex_unlock(&g_mut);
	return (ptr);
}
