/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   page.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaraval <tmaraval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/01 15:07:40 by tmaraval          #+#    #+#             */
/*   Updated: 2019/10/16 12:59:25 by tmaraval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

int		page_free_should_remove_page(t_zone **current_zone,
		t_chunk **chunk_check, t_chunk **chunk_keep, int p)
{
	int		state;
	int		i;

	state = 0;
	i = 0;
	if (p > 0 && *chunk_check && (*chunk_check)->prev 
	&& (void *)*chunk_check != (void *)(*current_zone) + getpagesize() * (p))
		*chunk_check = (*chunk_check)->prev;
	*chunk_keep = *chunk_check;
	while (*chunk_check && (void *)*chunk_check < (void *)(*current_zone) + getpagesize() * (p + 1))
	{
		if ((*chunk_check)->status == TO_REMOVE)
			state += 1;
		else
			state += (*chunk_check)->status;
		i++;
		*chunk_check = (*chunk_check)->next;
	}
	if (state == i && state != 0)
		return (1);
	return (0);
}

void	page_free_update_chunk_status(t_zone **current_zone,
		t_chunk **chunk_keep, int p)
{
	if (p > 0)
	{
		while (*chunk_keep && (void *)*chunk_keep
		< (void *)(*current_zone) + getpagesize() * (p + 1))
		{
			(*chunk_keep)->status = TO_REMOVE;	
			*chunk_keep = (*chunk_keep)->next;
		}
	(*current_zone)->state[p] = TO_FREE;
	}
}

void	page_free_fill_chunk_to_free(t_zone **current_zone)
{
	int		p;
	t_chunk *chunk_check;
	t_chunk *chunk_keep;

	p = 0;
	chunk_check = (*current_zone)->chunks;
	chunk_keep = chunk_check;
	while (p < (*current_zone)->pages_nbr)
	{
		if ((void *)*current_zone + (*current_zone)->used + sizeof(t_zone)
			> (void *)*current_zone + getpagesize() * (p + 1)
			&& (*current_zone)->state[p] != FREE)
		{
			if (page_free_should_remove_page(current_zone,
				&chunk_check, &chunk_keep, p) == 1)
					page_free_update_chunk_status(current_zone, &chunk_keep, p);
		}
		p++;
	}

}

void	page_free_remove_chunks(t_zone **current_zone)
{
	t_chunk *cpy;
	t_chunk *chunk_to_free;

	chunk_to_free = (*current_zone)->chunks;
	cpy = NULL;
	while (chunk_to_free)
	{
		cpy =  chunk_to_free;
		if (chunk_to_free->status == TO_REMOVE)
			delete_chunk(&((*current_zone)->chunks), chunk_to_free);
		chunk_to_free = cpy->next;
	}
}

void	page_free(t_zone **current_zone)
{
	int i;

	i = 0;
	page_free_fill_chunk_to_free(current_zone);
	page_free_remove_chunks(current_zone);
	while (i < (*current_zone)->pages_nbr)
	{
		if ((*current_zone)->state[i] == TO_FREE)
		{
			debug_munmap((void *)*current_zone + (getpagesize() * i),
					getpagesize());
			munmap((void *)*current_zone + (getpagesize() * i), getpagesize());
			(*current_zone)->state[i] = FREE;
		}
		i++;
	}
}
