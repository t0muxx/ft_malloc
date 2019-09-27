/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_malloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaraval <tmaraval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/26 16:08:55 by tmaraval          #+#    #+#             */
/*   Updated: 2019/09/27 09:28:57 by tmaraval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests.h"
#include "ft_malloc.h"

void test_malloc_simple(void)
{
	char *str;
	char *str2;
	
	str = (char *)ft_malloc(4);
	printf("str = %p\n", str);
	strcpy(str, "123");
	printf("str = %s\n", str);
	str2 = (char *)ft_malloc(8);
	printf("str2 = %p\n", str2);
	strcpy(str2, "abcdefg");
	assert(strcmp(str2, "abcdefg") == 0);
	printf("str2 = %s\n", str2);
	ft_free(str2);	
	str2 = (char *)ft_malloc(8);
	printf("str2 = %p\n", str2);
	strcpy(str2, "xzvbnmj");
	printf("str2 = %s\n", str2);
	assert(strcmp(str, "123") == 0);
	assert(strcmp(str2, "xzvbnmj") == 0);
}

void test_malloc_multiple(void)
{
	char *str;
	char *str2;
	int  i;

	i = 0;
	str = ft_malloc(623);
	while (i < 100)
	{
		str2 = ft_malloc(623);
		strcpy(str2, "test");
		i++;
	}
	str2 = ft_malloc(623);
	strcpy(str2, "test2");
	assert(strcmp(str2, "test2") == 0);
}
