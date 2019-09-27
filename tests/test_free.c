/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_free.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaraval <tmaraval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/26 15:38:40 by tmaraval          #+#    #+#             */
/*   Updated: 2019/09/26 15:49:38 by tmaraval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"
#include <assert.h>

void test_free_validChunk(void)
{
	t_chunk *chunk;
	void *mem;

	chunk = mmap(0, sizeof(t_chunk) + 16, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0);
	chunk->next = NULL;
	chunk->prev = NULL;
	chunk->size = 16;
	chunk->status = USED;
	mem = (void *)chunk + sizeof(t_chunk);
	ft_free(mem);
	assert(chunk->status == FREE);	

}
