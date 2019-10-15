/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaraval <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/15 16:43:17 by tmaraval          #+#    #+#             */
/*   Updated: 2019/10/15 16:55:35 by tmaraval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

extern pthread_mutex_t mut;

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

void	*ft_realloc(void *ptr, size_t size)
{
	t_chunk *chunk;
	void	*ret;

	ret = NULL;
	chunk = NULL;
	if (ptr == NULL)
		return (malloc(size));
	if (search_chunk(&(g_malloc_state.zone_tiny), ptr) == 0
	&& search_chunk(&(g_malloc_state.zone_medium), ptr) == 0
	&& search_chunk_large(&(g_malloc_state.zone_large), ptr) == 0)
		return (NULL);
	if (ptr != NULL && size == 0)
	{
		free(ptr);
		return (NULL);
	}
	if (search_chunk_large(&(g_malloc_state.zone_large), ptr) == 1)
		return (realloc_large(ptr, size));
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
