/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaraval <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/01 07:53:33 by tmaraval          #+#    #+#             */
/*   Updated: 2019/10/02 14:19:24 by tmaraval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_malloc.h>

int	init_malloc(void)
{
	if (g_malloc_state.zone_tiny == NULL)
	{
#ifdef DEBUG
//		printf("ZONE_TINY = %u\n", getpagesize() * MULTIPLE_ZONE_TINY);
//		printf("SZ_TINY = %lu\n", size_max(MULTIPLE_ZONE_TINY));
#endif
		if (add_zone(&(g_malloc_state.zone_tiny), MULTIPLE_ZONE_TINY) != 0)
		{
			ft_putendl_fd("malloc : error during init\n", 2);
			return (-1);
		}
	}
	return (0);
}
