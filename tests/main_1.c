/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaraval <tmaraval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/03 08:58:55 by tmaraval          #+#    #+#             */
/*   Updated: 2019/10/04 15:37:34 by tmaraval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
/*
int main(void)
{
	int value[] = {392, 31, 86, 23, 17, 19, 14, 17, 54,
		11, 15, 41, 32, 13, 23, 17, 28, 14, 29, 151, 31,
		15, 17, 21, 15, 21, 8, 41, 41, 20, 11, 14, 20, 23,
		 19, 27, 11, 8, 32, 46, 0};
	int i;
	void *ptr;

	i = 0;
	while (i < 2)
	{
		ptr = malloc(value[i]);
		if (ptr == NULL)
		{
			write(1, "ERROR \n", 8);
			return (1);
		}
		free(ptr);
		ptr = NULL;
		i++;
	}
	return (0);
}
*/

int main(void)
{
	int i;
	void *ptr;

	i = 0;
	ptr = NULL;
	write(1, "entry\n", 6);
	while (i < 50)
	{
		ptr = malloc(50 + i);
		if (ptr == NULL)
			write(1, "err\n", 4);
		i++;
	}
	i = 0;
	while (i < 50)
	{
		ptr = malloc(700 + i);
		if (ptr == NULL)
			write(1, "err\n", 4);
		i++;
	}
	ptr = malloc(4000);
	if (ptr == NULL)
		write(1, "err\n", 4);
	ptr = malloc(18*(1024*1024));
	if (ptr == NULL)
		write(1, "err\n", 4);
	write(1, "stop\n", 5);
	return (0);
}
