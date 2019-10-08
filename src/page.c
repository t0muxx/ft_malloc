/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   page.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaraval <tmaraval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/01 15:07:40 by tmaraval          #+#    #+#             */
/*   Updated: 2019/10/08 17:36:18 by tmaraval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

void	page_free_fill_chunk_to_free(t_zone **current_zone)
{
	int		p;
	t_chunk *chunk_check;
	t_chunk *chunk_keep;
	int		state;
	int		i;

	p = 0;
	chunk_check = (*current_zone)->chunks;
	chunk_keep = NULL;
	while (p < (*current_zone)->pages_nbr)
	{
		state = 0;
		i = 0;
		chunk_keep = chunk_check;
		ft_putstr("page = ");
		ft_putnbr(p);
		ft_putendl("");
		while (chunk_check && (void *)chunk_check < (void *)(*current_zone) + getpagesize() * (p + 1))
		{
			state += chunk_check->status;
			i++;
			chunk_check = chunk_check->next;
		}
		if (state == i && state != 0)
		{
			while (chunk_keep && (void *)chunk_keep < (void *)(*current_zone) + getpagesize() * (p + 1))
			{
				ft_putendl("added chunk : ");
				print_chunk(chunk_keep);
				chunk_keep->status = TO_REMOVE;	
				chunk_keep = chunk_keep->next;
			}
				(*current_zone)->state[p] = TO_FREE;
		}
		p++;
	}

}

void	page_free(t_zone **current_zone)
{
	t_chunk *chunk_to_free;
	t_chunk	*cpy;
	int i;

	i = 0;
	chunk_to_free = NULL;
	page_free_fill_chunk_to_free(current_zone);
	print_chunks((*current_zone)->chunks, "chunk to free : ");
	ft_putstr("page to free : \n");
	while (i < (*current_zone)->pages_nbr)
	{
		ft_putnbr(i);
		ft_putstr("  =  ");
		ft_putnbr((*current_zone)->state[i]);
		ft_putendl("");
		i++;
	}
	chunk_to_free = (*current_zone)->chunks;
	while (chunk_to_free)
	{
		cpy =  chunk_to_free;
		if (chunk_to_free->status == TO_REMOVE)
			delete_chunk(&((*current_zone)->chunks), chunk_to_free);
		chunk_to_free = cpy->next;
	}
	print_chunks((*current_zone)->chunks, "after delete");
	i = 0;
	while (i < (*current_zone)->pages_nbr)
	{
		if ((*current_zone)->state[i] == TO_FREE)
		{
			munmap(*current_zone + (getpagesize() * i), getpagesize());
			(*current_zone)->state[i] = FREE;
		}
		i++;
	}
}
