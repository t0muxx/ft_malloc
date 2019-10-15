/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaraval <tmaraval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/24 15:20:19 by tmaraval          #+#    #+#             */
/*   Updated: 2019/10/10 14:59:28 by tmaraval         ###   ########.fr       */
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
	pthread_mutex_lock(&mut);	
	ft_memcpy(ret, ptr, chunk_large->size);
	pthread_mutex_unlock(&mut);	
		free(ptr);
	}
	return (ret);
}

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

void	*ft_realloc(void *ptr, size_t size)
{
	t_chunk *chunk;
	void	*ret;

	pthread_mutex_lock(&mut);	
	ret = NULL;
	chunk = NULL;
	if (ptr == NULL)
	{
		pthread_mutex_unlock(&mut);	
		return (malloc(size));
	}
	if (search_chunk(&(g_malloc_state.zone_tiny), ptr) == 0
	&& search_chunk(&(g_malloc_state.zone_medium), ptr) == 0
	&& search_chunk_large(&(g_malloc_state.zone_large), ptr) == 0)
	{
		pthread_mutex_unlock(&mut);	
		return (NULL);
	}
	if (ptr != NULL && size == 0)
	{
		pthread_mutex_unlock(&mut);	
		free(ptr);
		return (0);
	}
	if (search_chunk_large(&(g_malloc_state.zone_large), ptr) == 1)
	{
		pthread_mutex_unlock(&mut);	
		return (realloc_large(ptr, size));
	}
	chunk = ptr - sizeof(t_chunk);
	if (size <= chunk->size)
	{
		pthread_mutex_unlock(&mut);	
		return (ptr);
	}
	else
	 {
		pthread_mutex_unlock(&mut);	
		if ((ret = malloc(size)) == NULL)
			return (NULL);
		pthread_mutex_lock(&mut);
		ft_memcpy(ret, ptr, chunk->size);
		pthread_mutex_unlock(&mut);	
		free(ptr);
	}
		pthread_mutex_unlock(&mut);	
	return (ret);
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	void *ptr;

	if ((ptr = malloc(nmemb * size)))
	pthread_mutex_lock(&mut);	
		ft_memset(ptr, 0, nmemb * size);
	pthread_mutex_unlock(&mut);	
	return (ptr);
}

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

void	free(void *ptr)
{
	pthread_mutex_lock(&mut);	
#ifdef DEBUG_FREE_RET
	ft_putstr("|DEBUG| -> asked for free(");
	ft_putptr(ptr);
	ft_putstr(");\n");
#endif
#ifdef DEBUG_FREE
	ft_putstr("|DEBUG| -> free(");
	ft_putptr(ptr);
	ft_putendl(")");
#endif
	ft_free(ptr);
	pthread_mutex_unlock(&mut);	
}

