/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaraval <tmaraval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/24 15:20:19 by tmaraval          #+#    #+#             */
/*   Updated: 2019/10/08 16:50:32 by tmaraval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

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
	ft_putnbr(size);
	ft_putstr(");\n");
#endif
	if ((int)size < 0)
	{
		return (NULL);
	}
	if (g_malloc_state.zone_tiny == NULL
			&& g_malloc_state.zone_medium == NULL
			&& init_malloc() != 0)
	{
		return (NULL);
	}
	if (size < size_max(MULTIPLE_ZONE_TINY))
	{
		return (malloc_not_large(&(g_malloc_state.zone_tiny), size));
	}
	else if (size < size_max(MULTIPLE_ZONE_MEDIUM))
	{
		return (malloc_not_large(&(g_malloc_state.zone_medium), size));
	}
	else 
	{
		return (malloc_large(&(g_malloc_state.zone_large), size));
	}
	return (NULL);
}

void	*realloc_large(void *ptr, size_t size)
{
	t_zone	*chunk_large;
	void	*ret;
	chunk_large = ptr - sizeof(t_zone);
	if (size <= chunk_large->size)
		return (ptr);
	else
	{
		if ((ret = malloc(size)) == NULL)
			return (NULL);
		ft_memcpy(ret, ptr, chunk_large->size);
		free(ptr);
	}
	return (ret);
}

void	*ft_realloc(void *ptr, size_t size)
{
	t_chunk *chunk;
	void	*ret;

	ret = NULL;
	chunk = NULL;
	if (ptr == NULL)
		return (ft_malloc(size));
	if (search_chunk(&(g_malloc_state.zone_tiny), ptr) == 0
	&& search_chunk(&(g_malloc_state.zone_medium), ptr) == 0
	&& search_chunk_large(&(g_malloc_state.zone_large), ptr) == 0)
	{
		return (NULL);
	}
	if (ptr != NULL && size == 0)
	{
		free(ptr);
		return (0);
	}
	if (search_chunk_large(&(g_malloc_state.zone_large), ptr) == 1)
		return (realloc_large(ptr, size));
	chunk = ptr - sizeof(t_chunk);
	if (size <= chunk->size)
	{
		return (ptr);
	}
	else
	{
		if ((ret = malloc(size)) == NULL)
			return (NULL);
		ft_memcpy(ret, ptr, size);
		free(ptr);
	}
	return (ret);
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	void *ptr;

	if ((ptr = malloc(nmemb * size)))
		ft_memset(ptr, 0, nmemb * size);
	return (ptr);
}
/*
void *calloc(size_t nmemb, size_t size)
{
	void *ret;

	ret = NULL;
#ifdef DEBUG_CALLOC
	ft_putstr("|DEBUG| -> calloc(");
	ft_putnbr(nmemb);
	ft_putstr(", ");
	ft_putnbr(size);
	ft_putendl(");");
#endif
	ret = ft_calloc(nmemb, size);
#ifdef DEBUG_CALLOC
	ft_putstr("|DEBUG| -> END | ret from caalloc : ");
	ft_putptr(ret);
	ft_putendl("");
#endif
	return (ret);
}

void	*realloc(void *ptr, size_t size)
{
	void *ret;

	ret = NULL;
#ifdef DEBUG_REALLOC
	ft_putstr("|DEBUG| -> realloc(");
	ft_putptr(ptr);
	ft_putstr(", ");
	ft_putnbr((int)size);
	ft_putendl(");");

#endif
	ret = ft_realloc(ptr, size);
#ifdef DEBUG_REALLOC
	ft_putstr("|DEBUG| -> END | ret from realloc : ");
	ft_putptr(ret);
	ft_putendl("");
#endif

	return (ret);
}

void	*malloc(size_t size)
{
	void *ptr;

	ptr = ft_malloc(size);
#ifdef DEBUG_MALLOC
	ft_putstr("|DEBUG| -> END | ret from malloc : ");
	ft_putptr(ptr);
	ft_putendl("");
#endif
	return (ptr);
}

void	free(void *ptr)
{
#ifdef DEBUG_FREE_RET
	ft_putstr("|DEBUG| -> asked for free(");
	ft_putptr(ptr);
	ft_putstr(");\n");
#endif
	ft_free(ptr);
}*/
