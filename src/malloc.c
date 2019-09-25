/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaraval <tmaraval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/24 15:20:19 by tmaraval          #+#    #+#             */
/*   Updated: 2019/09/25 08:58:15 by tmaraval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"
#include "libft.h"

t_malloc g_malloc = {NULL};

void *malloc_tiny(size_t size)
{
	if (size)
	{
	}
	return (NULL);
}

void *ft_malloc(size_t size)
{
	if (size < 0)
	{
		return NULL;
	}
	if (init_malloc(&g_malloc) != 0)
	{
		// manage error
	}
	if (size < SZ_TINY)
	{
		return(malloc_tiny(size));
	}
	return (NULL);
}
