/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaraval <tmaraval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/25 10:51:30 by tmaraval          #+#    #+#             */
/*   Updated: 2019/10/03 08:46:42 by tmaraval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

void print_chunk(t_chunk *tmp)
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
	ft_putstr("--- next -----\n");
}

void print_chunks(t_chunk *chunk, char * chunk_name)
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
/*
	printf("|DEBUG| -> NOW BACKWARDS\n");
	tmp = prev;
	while (tmp != NULL)
	{
		printf("|DEBUG| -> chunk->status = %lu\n", tmp->status);
		printf("|DEBUG| -> chunk->size = %lu\n", tmp->size);
		printf("|DEBUG| -> chunk->prev = %p\n", tmp->prev);
		printf("|DEBUG| -> chunk->next = %p\n", tmp->next);
		printf("|DEBUG| -> chunk->dataAddr = %p\n", (void *)tmp + sizeof(t_chunk));
		printf("|DEBUG| -> chunk->data = %s\n", (char *)((void *)tmp + sizeof(t_chunk)));
		printf("--- next -----\n");
		tmp = tmp->prev;
	}
	*/
}

void print_zones(t_zone *zone, char *zone_name)
{
	t_zone *tmp;
	int i;

	i = 0;
	tmp = zone;
	ft_putstr("|DEBUG| -> zone in : ");
	ft_putendl(zone_name);
	while (tmp != NULL)
	{
		ft_putstr("|DEBUG| -> page num : ");
		ft_putnbr(i);
		ft_putendl("");
		ft_putstr("|DEBUG| -> zone->size : ");
		ft_putnbr(zone->size);
		ft_putendl("");
		ft_putstr("|DEBUG| -> zone->used : ");
		ft_putnbr(zone->used);
		ft_putendl("");
		
		ft_putstr("|DEBUG| -> Addr space ");
		ft_putptr(zone_2_mem(tmp));
		ft_putstr(" - ");
		ft_putptr(zone_2_mem(tmp) + tmp->size);
		ft_putendl("");
		i++;
		tmp = tmp->next;
	}
}
