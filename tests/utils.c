/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaraval <tmaraval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/27 11:14:17 by tmaraval          #+#    #+#             */
/*   Updated: 2019/09/27 11:16:59 by tmaraval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"
#include "tests.h"

int cnt_chunks(t_chunk **head, size_t status)
{
	t_chunk *tmp;
	int i = 0;

	tmp = *head;
	while (tmp != NULL)
	{
		if (tmp->status == status)
			i++;
		tmp = tmp->next;
	}
	return (i);
}
