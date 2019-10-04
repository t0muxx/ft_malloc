/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaraval <tmaraval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/25 14:51:56 by tmaraval          #+#    #+#             */
/*   Updated: 2019/10/04 17:38:37 by tmaraval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

size_t aligne_large(size_t size)
{
	return (size + getpagesize() - (size % getpagesize()));
}

size_t	size_max(size_t multiple)
{
	size_t size_zone;
	size_t size_max;

	size_zone = getpagesize() * multiple - sizeof(t_zone);
	size_max = ((size_zone / 100)
		- (ALIGN - ((size_zone / 100) - sizeof(struct s_chunk)) % 16));
	return (size_max);
}

int		cnt_zone(t_zone *zone)
{
	int i;

	i = 0;
	while (zone)
	{
		i++;
		zone = zone->next;
	}
	return (i);
}

void	*zone_2_mem(t_zone *zone)
{
	return ((void *)zone + sizeof(t_zone));
}

t_zone	*mem_2_zone(void *mem)
{
	return ((t_zone *)mem - sizeof(t_zone));
}
