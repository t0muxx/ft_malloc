/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: t0mux </var/spool/mail/t0mux>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/24 17:10:11 by t0mux             #+#    #+#             */
/*   Updated: 2019/09/25 15:53:59 by tmaraval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_malloc.h>

int init_malloc(t_malloc *g_malloc)
{
	if (g_malloc->zone_tiny == NULL) 
	{
#ifdef DEBUG
	printf("ZONE_TINY = %d\n", SZ_ZONE_TINY);
	printf("SZ_TINY = %lu\n", SZ_TINY);
#endif
		if (add_zone(&(g_malloc->zone_tiny), SZ_ZONE_TINY) != 0)
		{
			ft_putendl_fd("malloc : error during init\n", 2);
			return (-1);
		}
	}
	return (0);
}
