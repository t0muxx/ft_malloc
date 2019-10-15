/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_size.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaraval <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/15 16:45:31 by tmaraval          #+#    #+#             */
/*   Updated: 2019/10/15 16:45:53 by tmaraval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

size_t	malloc_good_size(size_t size)
{
	return (ALIGN_SIZE(size));
}

size_t	malloc_size(const void *ptr_const)
{
	void	*ptr;
	t_chunk *chunk;
	t_zone	*zone;

	chunk = NULL;
	zone = NULL;
	ptr = (void *)ptr_const;
	if (search_chunk(&(g_malloc_state.zone_tiny), ptr) == 0
	&& search_chunk(&(g_malloc_state.zone_medium), ptr) == 0
	&& search_chunk_large(&(g_malloc_state.zone_large), ptr) == 0)
	{
		return (0);
	}
	else if (search_chunk(&(g_malloc_state.zone_tiny), ptr)
			|| search_chunk(&(g_malloc_state.zone_medium), ptr))
	{
		chunk = ptr - sizeof(t_chunk);
		return (chunk->size);
	}
	else
	{
		zone = ptr - sizeof(t_zone);
		return (zone->size);
	}
	return (0);
}
