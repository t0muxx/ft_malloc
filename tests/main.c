/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaraval <tmaraval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/24 16:21:20 by tmaraval          #+#    #+#             */
/*   Updated: 2019/09/27 09:23:12 by tmaraval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "../inc/ft_malloc.h"
#include "tests.h"

int main(void)
{
	test_free_validChunk();
//	test_init_ok();
//	test_init_alreadyInit();
	test_malloc_simple();
	test_malloc_multiple();
	return (0);
}

/*int main(void)
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

	

}*/
