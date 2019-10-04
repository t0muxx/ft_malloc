/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chunks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaraval <tmaraval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/27 16:12:02 by tmaraval          #+#    #+#             */
/*   Updated: 2019/10/03 12:54:09 by tmaraval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

void	delete_chunk(t_chunk **head, t_chunk *to_delete)
{
	if (*head == NULL || to_delete == NULL)
		return ;
	if (*head == to_delete)
		*head = to_delete->next;
	if (to_delete->next != NULL)
		to_delete->next->prev = to_delete->prev;
	if (to_delete->prev != NULL)
		to_delete->prev->next = to_delete->next;
}

void	add_chunk(t_chunk **head, void *zone_base, size_t sz_aligned)
{
	t_chunk *tmp;
	t_chunk *new;

	new = zone_base;
	new->status = USED;
	new->size = sz_aligned;
	new->prev = NULL;
	new->next = NULL;
	tmp = *head;
	if (*head == NULL)
	{
		*head = new;
		return ;
	}
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = new;
	new->prev = tmp;
}

int		search_chunk(t_chunk *chunk)
{
	t_zone	*zones;
	t_chunk	*chunks;
	zones = g_malloc_state.zone_tiny;
	chunks = zones->chunks;
	while (chunks)
	{
		if (chunk == chunks)
			return (1);
		chunks = chunks->next;
	}
	return (0);
}

void	*search_free_chunk(t_zone *head, size_t sz_aligned)
{
	t_zone	*tmp_zone;
	t_chunk *tmp_chunk;

	tmp_zone = head;
	while (tmp_zone != NULL)
	{
		tmp_chunk = tmp_zone->chunks;
		while (tmp_chunk != NULL)
		{
			if (tmp_chunk->status == FREE && tmp_chunk->size == sz_aligned)
			{
				tmp_chunk->status = USED;
				return ((void *)tmp_chunk + sizeof(t_chunk));
			}
			tmp_chunk = tmp_chunk->next;
		}
		tmp_zone = tmp_zone->next;
	}
	return (NULL);
}
