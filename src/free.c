/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaraval <tmaraval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/25 11:30:28 by tmaraval          #+#    #+#             */
/*   Updated: 2019/09/25 15:50:22 by tmaraval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

void ft_free(void *ptr)
{
	t_chunk *tmp;

#ifdef DEBUG_FREE
	printf("|DEBUG| -> before free\n");
	print_chunks(g_malloc.chunk_tiny, "chunk_tiny");
#endif
	tmp = ptr - sizeof(t_chunk);
	tmp->status = FREE;
#ifdef DEBUG_FREE
	printf("|DEBUG| -> after free\n");
	print_chunks(g_malloc.chunk_tiny, "chunk_tiny");
#endif
}
