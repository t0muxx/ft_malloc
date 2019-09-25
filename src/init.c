/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: t0mux </var/spool/mail/t0mux>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/24 17:10:11 by t0mux             #+#    #+#             */
/*   Updated: 2019/09/25 09:39:34 by tmaraval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_malloc.h>

int init_malloc(t_malloc *g_malloc)
{
	void *mem;
	
	if (g_malloc->zone_tiny == NULL) 
	{
		mem = mmap(0, sizeof(t_zone) + SZ_TINY, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0);
#ifdef DEBUG
	printf("|DEBUG| -> mmaped zone_tiny : %lu\n", sizeof(t_zone) + SZ_TINY);
#endif
		if (mem == MAP_FAILED) 
		{
			perror("zone_tiny : ");
			ft_putendl_fd("malloc : can't mmap memory for zone_tiny", 2);
			return (-1);
		}
		g_malloc->zone_tiny = mem;
		g_malloc->zone_tiny->size = SZ_TINY;
		g_malloc->zone_tiny->used = 0;
		ft_memset((void *)ZONE2MEM(g_malloc->zone_tiny), 0, SZ_TINY);
#ifdef DEBUG
	printf("|DEBUG| -> g_malloc->zone_tiny->size : %zu\n", g_malloc->zone_tiny->size);
	printf("|DEBUG| -> g_malloc->zone_tiny->used : %zu\n", g_malloc->zone_tiny->used);
	printf("|DEBUG| -> g_malloc->zone_tiny : %p\n", (void *)g_malloc->zone_tiny);
	printf("|DEBUG| -> g_malloc->zone_tiny (memoire) : %p\n", ZONE2MEM(g_malloc->zone_tiny));
	printf("|DEBUG| -> sizeof : %lu\n", sizeof(t_zone));
#endif
	}
	return (0);
}
