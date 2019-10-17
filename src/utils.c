/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaraval <tmaraval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/25 14:51:56 by tmaraval          #+#    #+#             */
/*   Updated: 2019/10/17 10:42:06 by tmaraval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

void	init_opt(unsigned long *opt)
{
	if (!(*opt & OPT_SET))
		*opt |= 1UL << 10;
	if (getenv("DEBUG_FREE"))
		*opt |= 1UL << 0;
	if (getenv("DEBUG_FREE_MEM"))
		*opt |= 1UL << 1;
	if (getenv("DEBUG_MALLOC"))
		*opt |= 1UL << 2;
	if (getenv("DEBUG_MALLOC_RET"))
		*opt |= 1UL << 3;
	if (getenv("DEBUG_CALLOC"))
		*opt |= 1UL << 4;
	if (getenv("DEBUG_CALLOC_RET"))
		*opt |= 1UL << 5;
	if (getenv("DEBUG_REALLOC"))
		*opt |= 1UL << 6;
	if (getenv("DEBUG_REALLOC_RET"))
		*opt |= 1UL << 7;
	if (getenv("DEBUG_MUNMAP"))
		*opt |= 1UL << 8;
	if (getenv("DEBUG_MMAP"))
		*opt |= 1UL << 9;
}

size_t	aligne_large(size_t size)
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
