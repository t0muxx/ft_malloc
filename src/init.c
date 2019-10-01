/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaraval <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/01 07:53:33 by tmaraval          #+#    #+#             */
/*   Updated: 2019/10/01 07:57:50 by tmaraval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_malloc.h>
#include <unistd.h>

int	init_malloc(void)
{
	int pagesize;

	pagesize = getpagesize();
	if (g_malloc.zone_tiny == NULL)
	{
		// need to change this shit
		g_malloc.size = mmap(0, sizeof(t_size), PROT_READ | PROT_WRITE,
				MAP_SHARED | MAP_ANONYMOUS, -1, 0);
		if (g_malloc.size == MAP_FAILED)
		{
			ft_putendl_fd("malloc : can't mmap memory for g_malloc.size", 2);
			return (-1);
		}
		g_malloc.size->sz_zone_tiny = pagesize * MULTIPLE_ZONE_TINY;
		g_malloc.size->sz_tiny = ((g_malloc.size->sz_zone_tiny / 100) -
		sizeof(struct s_chunk)) + (ALIGN - ((g_malloc.size->sz_zone_tiny / 100)
		- sizeof(struct s_chunk)) % 16);
		g_malloc.size->sz_min_alloc_tiny = ALIGN;
#ifdef DEBUG
		printf("ZONE_TINY = %lu\n", g_malloc.size->sz_zone_tiny);
		printf("SZ_TINY = %lu\n", g_malloc.size->sz_tiny);
#endif
		if (add_zone(&(g_malloc.zone_tiny), MULTIPLE_ZONE_TINY) != 0)
		{
			ft_putendl_fd("malloc : error during init\n", 2);
			return (-1);
		}
	}
	return (0);
}
