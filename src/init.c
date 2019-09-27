/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: t0mux </var/spool/mail/t0mux>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/24 17:10:11 by t0mux             #+#    #+#             */
/*   Updated: 2019/09/27 10:24:44 by tmaraval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_malloc.h>
#include <unistd.h>

int init_malloc()
{
	int pagesize;

	pagesize = getpagesize();
	if (g_malloc.zone_tiny == NULL) 
	{
	g_malloc.size = mmap(0, sizeof(t_size), PROT_READ|PROT_WRITE, MAP_SHARED|MAP_ANONYMOUS, -1, 0);
	if (g_malloc.size == MAP_FAILED)
	{
		ft_putendl_fd("malloc : can't mmap memory for g_malloc.size", 2);
		return (-1);
	}
	g_malloc.size->sz_zone_tiny = pagesize * MULTIPLE_ZONE_TINY;
	g_malloc.size->sz_tiny = ((g_malloc.size->sz_zone_tiny/100)-
		sizeof(struct s_chunk))+(ALIGN-((g_malloc.size->sz_zone_tiny/100)
		-sizeof(struct s_chunk))%16);
	g_malloc.size->sz_min_alloc_tiny = ALIGN;
#ifdef DEBUG
	printf("ZONE_TINY = %lu\n", g_malloc.size->sz_zone_tiny);
	printf("SZ_TINY = %lu\n", g_malloc.size->sz_tiny);
#endif
		if (add_zone(&(g_malloc.zone_tiny), g_malloc.size->sz_zone_tiny) != 0)
		{
			ft_putendl_fd("malloc : error during init\n", 2);
			return (-1);
		}
	}
	return (0);
}
