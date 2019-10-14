/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaraval <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/01 07:53:33 by tmaraval          #+#    #+#             */
/*   Updated: 2019/10/03 17:19:42 by tmaraval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_malloc.h>

int	init_malloc(void)
{
#ifdef DEBUG
#endif
	if (g_malloc_state.zone_tiny == NULL)
	{
		if (add_zone(&(g_malloc_state.zone_tiny), MULTIPLE_ZONE_TINY) != 0)
		{
			ft_putendl_fd("malloc : error during init\n", 2);
			return (-1);
		}
	}
	if (g_malloc_state.zone_medium == NULL)
	{
		if (add_zone(&(g_malloc_state.zone_medium), MULTIPLE_ZONE_MEDIUM) != 0)
		{
			ft_putendl_fd("malloc : error during init\n", 2);
			return (-1);
		}
	}
	return (0);
}
