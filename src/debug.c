/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaraval <tmaraval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/25 10:51:30 by tmaraval          #+#    #+#             */
/*   Updated: 2019/10/11 14:09:07 by tmaraval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

void	print_state(enum e_status state)
{
	if (state == 0)
		ft_putstr("USED");
	if (state == 1)
		ft_putstr("FREE");
	if (state == 2)
		ft_putstr("TO_FREE");
	if (state == 3)
		ft_putstr("TO_REMOVE");
}

void	debug_all(t_malloc *state)
{
	ft_putendl("|DEBUG| -> STATE OF TINY : ");
	print_zones(state->zone_tiny, "TINY ");
	ft_putendl("|DEBUG| -> STATE OF MEDIUM : ");
	print_zones(state->zone_medium, "MEDIUM ");
	ft_putendl("|DEBUG| -> STATE OF LARGE : ");
	print_zones(state->zone_large, "LARGE ");
}

void	cnt_total_zone()
{
	t_zone *zone;
	int i;

	i = 0;
	zone = g_malloc_state.zone_tiny;
	while (zone)
	{
		i++;
		zone = zone->next;
	}
	zone = g_malloc_state.zone_medium;
	while (zone)
	{
		i++;
		zone = zone->next;
	}
	zone = g_malloc_state.zone_large;
	while (zone)
	{		
		i++;
		zone = zone->next;
	}
	ft_putstr("|DEBUG| -> total zone : ");
	ft_putnbr(i);
	ft_putendl("");

}

void	print_chunk(t_chunk *tmp)
{
	ft_putendl("|DEBUG| -> SOLO CHUNKS");
	ft_putstr("|DEBUG| -> chunk = ");
	ft_putptr(tmp);
	ft_putendl("");
	ft_putstr("|DEBUG| -> chunk->status = ");
	ft_putnbr((int)tmp->status);
	ft_putendl("");
	ft_putstr("|DEBUG| -> chunk->size = ");
	ft_putnbr((int)tmp->size);
	ft_putendl("");
	ft_putstr("|DEBUG| -> chunk->prev = ");
	ft_putptr(tmp->prev);
	ft_putendl("");
	ft_putstr("|DEBUG| -> chunk->next = ");
	ft_putptr(tmp->next);
	ft_putendl("");
	ft_putstr("|DEBUG| -> chunk->dataAddr = ");
	ft_putptr((void *)tmp + sizeof(t_chunk));
	ft_putendl("");
	ft_putstr("--- END -----\n");
}

void	print_chunks(t_chunk *chunk, char *chunk_name)
{
	t_chunk *tmp;

	tmp = chunk;
	ft_putstr("|DEBUG| -> chunks in : ");
	ft_putendl(chunk_name);
	while (tmp != NULL)
	{
		ft_putstr("|DEBUG| -> chunk = ");
		ft_putptr(tmp);
		ft_putendl("");
		ft_putstr("|DEBUG| -> chunk->status = ");
		ft_putnbr((int)tmp->status);
		ft_putendl("");
		ft_putstr("|DEBUG| -> chunk->size = ");
		ft_putnbr((int)tmp->size);
		ft_putendl("");
		ft_putstr("|DEBUG| -> chunk->prev = ");
		ft_putptr(tmp->prev);
		ft_putendl("");
		ft_putstr("|DEBUG| -> chunk->next = ");
		ft_putptr(tmp->next);
		ft_putendl("");
		ft_putstr("|DEBUG| -> chunk->dataAddr = ");
		ft_putptr((void *)tmp + sizeof(t_chunk));
		ft_putendl("");
		ft_putstr("--- next -----\n");
		tmp = tmp->next;
	}
	ft_putstr("--- END -----\n");
}

void	print_zones(t_zone *zone, char *zone_name)
{
	t_zone	*tmp;
	int		i;
	int		j;

	i = 0;
	tmp = zone;
	ft_putstr("|DEBUG| -> zone in : ");
	ft_putendl(zone_name);
	while (tmp != NULL)
	{
		j = 0;
		ft_putstr("|DEBUG| -> zone num : ");
		ft_putnbr(i);
		ft_putendl("");
		ft_putstr("|DEBUG| -> zone : ");
		ft_putptr(tmp);
		ft_putendl("");
		ft_putstr("|DEBUG| -> zone->next : ");
		ft_putptr(tmp->next);
		ft_putendl("");
		ft_putstr("|DEBUG| -> zone->size : ");
		ft_putnbr(tmp->size);
		ft_putendl("");
		ft_putstr("|DEBUG| -> zone->used : ");
		ft_putnbr(tmp->used);
		ft_putendl("");
		ft_putstr("|DEBUG| -> Page state : \n");
		while (j < tmp->pages_nbr)
		{
			ft_putstr("page : ");
			ft_putnbr(j);
			ft_putstr(" ; status -> ");
			print_state(tmp->state[j]);
			ft_putendl("");
			j++;
		}
		ft_putstr("|DEBUG| -> Addr space ");
		ft_putptr(zone_2_mem(tmp));
		ft_putstr(" - ");
		ft_putptr(zone_2_mem(tmp) + tmp->size);
		ft_putendl("");
		//print_chunks(tmp->chunks, "chunks : ");
		ft_putendl("\n----------------- NEXT ->");
		i++;
		tmp = tmp->next;
	}
	ft_putendl("---------------- END -----");
}
