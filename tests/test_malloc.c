/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_malloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaraval <tmaraval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/26 16:08:55 by tmaraval          #+#    #+#             */
/*   Updated: 2019/10/02 13:07:51 by tmaraval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests.h"
#include "ft_malloc.h"

void test_malloc_simple(void **state)
{
	char *ptr1;
	char *ptr2;
	t_chunk *chunk1;
	t_chunk *chunk2;

	ptr1 = NULL;
	ptr2 = NULL;
	ptr1 = ft_malloc(5);
	ptr2 = ft_malloc(10);
	chunk1 = (void *)ptr1 - sizeof(t_chunk);	
	chunk2 = (void *)ptr2 - sizeof(t_chunk);
	assert_int_equal(chunk1->status, USED);
	assert_int_equal(chunk2->status, USED);
	strcpy(ptr1, "test");
	strcpy(ptr2, "test2");
	assert_string_equal(ptr1, "test");
	assert_string_equal(ptr2, "test2");
	ft_free(ptr1);
	ft_free(ptr2);
	assert_int_equal(chunk1->status, FREE);
	assert_int_equal(chunk2->status, FREE);
}
