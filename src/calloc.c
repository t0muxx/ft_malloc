/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaraval <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/15 16:46:06 by tmaraval          #+#    #+#             */
/*   Updated: 2019/10/15 16:46:44 by tmaraval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

extern pthread_mutex_t mut;

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
