/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_malloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaraval <tmaraval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/26 16:08:55 by tmaraval          #+#    #+#             */
/*   Updated: 2019/10/10 14:26:57 by tmaraval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests.h"
#include "ft_malloc.h"

void	test_malloc_buggy(void **state)
{
	int i;
	void *ptr[4090];

	i = 0;
	while (i < 4090)
	{
		ptr[i] = ft_malloc(12);
		i++;
	}
	i = 0;
	while (i < 4090)
	{
		ft_free(ptr[i]);
		i++;
	}
}

void test_malloc_multiple(void **state)
{
	int value[] = {392, 31, 86, 23, 17, 19, 14, 17, 54,
		11, 15, 41, 32, 13, 23, 17, 28, 14, 29, 151, 31,
		15, 17, 21, 15, 21, 8, 41, 41, 20, 11, 14, 20, 23,
		 19, 27, 11, 8, 32, 0};
	int i;
	void *ptr;

	i = 0;
	while (value[i] != 0)
	{
		ptr = ft_malloc(value[i]);
		assert_non_null(ptr);
		ptr = NULL;
		i++;
	}
}

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
