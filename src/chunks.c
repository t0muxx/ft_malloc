/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chunks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaraval <tmaraval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/27 16:12:02 by tmaraval          #+#    #+#             */
/*   Updated: 2019/10/01 10:36:04 by tmaraval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

void	delete_chunk(t_chunk **head, t_chunk *toDelete)
{
	if (*head == NULL || toDelete == NULL)
		return ;
	if (*head == toDelete)
		*head = toDelete->next;
	if (toDelete->next != NULL)
		toDelete->next->prev = toDelete->prev;
	if (toDelete->prev != NULL)
		toDelete->prev->next = toDelete->next;
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

void	*search_chunk(t_zone *head, size_t sz_aligned)
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
