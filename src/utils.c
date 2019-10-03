/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaraval <tmaraval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/25 14:51:56 by tmaraval          #+#    #+#             */
/*   Updated: 2019/10/03 13:08:25 by tmaraval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

size_t	size_max(size_t multiple)
{
	size_t size_zone;
	size_t size_max;

	size_zone = getpagesize() * multiple;
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
	return ((void *)zone + getpagesize());
}

t_zone	*mem_2_zone(void *mem)
{
	return ((t_zone *)mem - getpagesize());
}
