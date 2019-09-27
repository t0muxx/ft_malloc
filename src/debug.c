/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaraval <tmaraval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/25 10:51:30 by tmaraval          #+#    #+#             */
/*   Updated: 2019/09/26 14:57:30 by tmaraval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

void print_chunks(t_chunk *chunk, char * chunk_name)
{
	t_chunk *tmp;

	tmp = chunk;
		printf("|DEBUG| -> chunks in : %s\n", chunk_name);
	while (tmp != NULL)
	{
		printf("|DEBUG| -> chunk->status = %lu\n", tmp->status);
		printf("|DEBUG| -> chunk->size = %lu\n", tmp->size);
		printf("|DEBUG| -> chunk->prev = %p\n", tmp->prev);
		printf("|DEBUG| -> chunk->next = %p\n", tmp->next);
		printf("|DEBUG| -> chunk->dataAddr = %p\n", (void *)tmp + sizeof(t_chunk));
		printf("|DEBUG| -> chunk->data = %s\n", (char *)((void *)tmp + sizeof(t_chunk)));
		printf("--- next -----\n");
		tmp = tmp->next;
	}
}

void print_zones(t_zone *zone, char *zone_name)
{
	t_zone *tmp;
	int i;

	i = 0;
	tmp = zone;
	printf("|DEBUG| -> zone in : %s\n", zone_name);
	while (tmp != NULL)
	{
		printf("|DEBUG| -> page num : %d\n", i);
		printf("|DEBUG| -> zone->size = %lu\n", tmp->size);
		printf("|DEBUG| -> zone->used = %lu\n", tmp->used);
		printf("|DEBUG| -> Addr space %p - %p\n", zone_2_mem(tmp), zone_2_mem(tmp) + tmp->size);
		i++;
		tmp = tmp->next;
	}
}
