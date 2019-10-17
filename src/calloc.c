/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaraval <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/15 16:46:06 by tmaraval          #+#    #+#             */
/*   Updated: 2019/10/17 12:05:14 by tmaraval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

extern pthread_mutex_t	g_mut;
extern t_malloc			g_malloc_state;

void	*ft_calloc(size_t nmemb, size_t size)
{
	void *ptr;

	if ((ptr = malloc(nmemb * size)))
	{
		pthread_mutex_lock(&g_mut);
		ft_memset(ptr, 0, nmemb * size);
		pthread_mutex_unlock(&g_mut);
	}
	return (ptr);
}

void	*calloc(size_t nmemb, size_t size)
{
	void *ret;

	ret = NULL;
	if (g_malloc_state.opt & DEBUG_CALLOC)
	{
		ft_putstr("|DEBUG| -> calloc(");
		ft_putnbr(nmemb);
		ft_putstr(", ");
		ft_putnbr(size);
		ft_putendl(");");
	}
	ret = ft_calloc(nmemb, size);
	if (g_malloc_state.opt & DEBUG_CALLOC_RET)
	{
		ft_putstr("|DEBUG| -> ret from calloc : ");
		ft_putptr(ret);
		ft_putendl("");
	}
	return (ret);
}
