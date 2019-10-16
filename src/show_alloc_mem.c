/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaraval <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/01 07:53:33 by tmaraval          #+#    #+#             */
/*   Updated: 2019/10/16 08:02:30 by tmaraval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

void	show_alloc_mem_print_chunks(t_chunk *chunks)
{
	t_chunk *chunk;

	chunk = chunks;
	while (chunk != NULL)
	{
		ft_putptr((void *)chunk + sizeof(t_chunk));
		ft_putstr(" - ");
		ft_putptr((void *)chunk + sizeof(t_chunk) + chunk->size);
		ft_putstr(" : ");
		ft_putnbr(chunk->size);
		ft_putstr(" octets\n");
		chunk = chunk->next;
	}
}

void	show_alloc_mem_print_large(t_zone *zones)
{
	t_zone *zone;
	
	zone = zones;
	while (zone)
	{
		ft_putstr("LARGE : ");
		ft_putptr(zone);
		ft_putendl("");
		ft_putptr(zone + sizeof(t_zone));
		ft_putstr(" - ");
		ft_putptr((void *)zone + sizeof(t_zone) + zone->size);
		ft_putstr(" : ");
		ft_putnbr(zone->size);
		ft_putstr(" octets\n");
		zone = zone->next;
	}
}

void	show_alloc_mem_print_small(t_zone *zones, char *size)
{
	t_zone *zone;

	zone = zones;
	while (zone != NULL)
	{
		ft_putstr(size);
		ft_putstr(" : ");
		ft_putptr(zone);
		ft_putendl("");
		show_alloc_mem_print_chunks(zone->chunks);
		zone = zone->next;
	}
}

void	show_alloc_mem()
{
	show_alloc_mem_print_small(g_malloc_state.zone_tiny, "TINY");	
	show_alloc_mem_print_small(g_malloc_state.zone_medium, "MEDIUM");
	show_alloc_mem_print_large(g_malloc_state.zone_large);
}
