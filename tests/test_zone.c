/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_zone.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaraval <tmaraval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/27 14:09:07 by tmaraval          #+#    #+#             */
/*   Updated: 2019/10/01 08:09:28 by tmaraval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"
#include "tests.h"

void test_search_zone_needAdd(void **state)
{
	t_zone *zone;
	t_zone *ret;

	ret = NULL;
	zone = NULL;
	add_zone(&zone, 16);
	assert_ptr_not_equal(zone, NULL);
	assert_int_equal(zone->size, 4096*16);
	assert_int_equal(zone->used, 0);
	zone->used = getpagesize() * 15;
	ret = search_zone(&zone, getpagesize());
	assert_ptr_not_equal(zone, ret);
	assert_int_equal(zone->next->used, 0);
}


void test_search_zone_same(void **state)
{
	t_zone *zone;
	
	zone = NULL;
	add_zone(&zone, 16);
	assert_ptr_not_equal(zone, NULL);
	assert_int_equal(zone->size, 4096*16);
	assert_int_equal(zone->used, 0);
	assert_ptr_equal(search_zone(&zone, 32), zone);
}

void test_add_zone_after(void **state)
{
	t_zone *zone;
	
	zone = NULL;
	add_zone(&zone, 16);
	assert_ptr_not_equal(zone, NULL);
	assert_int_equal(zone->size, 4096*16);
	assert_int_equal(zone->used, 0);
	assert_int_equal(zone->pages_nbr, 16);
	assert_ptr_equal(zone->chunks, NULL);
	assert_int_equal(add_zone(&zone,16), 0);
	assert_int_equal(zone->next->size, 4096*16);
	assert_int_equal(zone->next->used, 0);
	assert_int_equal(zone->next->pages_nbr, 16);
	assert_ptr_equal(zone->next->chunks, NULL);
}

void test_add_zone_null(void **state)
{
	t_zone *zone;

	zone = NULL;
	assert_int_equal(add_zone(&zone,16), 0);
	assert_ptr_not_equal(zone, NULL);
	assert_int_equal(zone->size, 4096*16);
	assert_int_equal(zone->used, 0);
	assert_int_equal(zone->pages_nbr, 16);
	assert_ptr_equal(zone->chunks, NULL);
}
