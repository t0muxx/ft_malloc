/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaraval <tmaraval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/24 16:21:20 by tmaraval          #+#    #+#             */
/*   Updated: 2019/09/25 16:01:26 by tmaraval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "../inc/ft_malloc.h"

int main(void)
{
	char *str;
	char *str2;
	int i = 0;

	while (i < 100)
	{
		ft_malloc(8);
		i++;
	}
	ft_malloc(10);
	ft_malloc(10);
	return (0);
/*
	str = (char *)ft_malloc(4);
	printf("str = %p\n", str);
	strcpy(str, "123");
	printf("str = %s\n", str);
	str2 = (char *)ft_malloc(8);
	printf("str2 = %p\n", str2);
	strcpy(str2, "abcdefg");
	printf("str2 = %s\n", str2);
	ft_free(str2);	
	str2 = (char *)ft_malloc(8);
	printf("str2 = %p\n", str2);
	strcpy(str2, "xzvbnmj");
	printf("str2 = %s\n", str2);
	return(0);
	*/

}
