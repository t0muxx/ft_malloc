/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaraval <tmaraval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/25 10:51:30 by tmaraval          #+#    #+#             */
/*   Updated: 2019/09/25 11:38:23 by tmaraval         ###   ########.fr       */
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
		printf("|DEBUG| -> chunk->data = %s\n", (void *)tmp + sizeof(t_chunk));
		printf("--- next -----\n");
		tmp = tmp->next;
	}
}
