/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_page.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaraval <tmaraval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/01 15:24:03 by tmaraval          #+#    #+#             */
/*   Updated: 2019/10/04 17:31:57 by tmaraval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"
#include "tests.h"

void	test_page_free_Page16ToFree(void **state)
{
	t_zone *zone;
	t_chunk *ck;
	int		i;

	i = 0;
	ck = NULL;
	zone = NULL;
	add_zone(&zone, 16);
	assert_ptr_not_equal(zone, NULL);
	assert_ptr_not_equal(zone_2_mem(zone), NULL);
	zone->chunks = NULL;
	assert_ptr_equal(zone->chunks, NULL);
	
	while (i < 15)
	{
		add_chunk(&(zone->chunks), zone_2_mem(zone)+ zone->used, 4064);
		zone->used += 4064 + sizeof(t_chunk);
		i++;
	}
	add_chunk(&(zone->chunks), zone_2_mem(zone) + zone->used, 4064);
	zone->chunks->next->next->next->next->next->next->next->next->next->next->next->next->next->next->status = FREE;
	zone->chunks->next->next->next->next->next->next->next->next->next->next->next->next->next->next->next->status = FREE;
	zone->used += 4064 + sizeof(t_chunk);
	assert_int_equal(cnt_chunks(&(zone->chunks), USED), 14);
	page_free(&zone, zone->pages_nbr);
}

void	test_page_free_Page2ToFree(void **state)
{
	t_zone *zone;
	t_chunk *ck;
	int i;

	i = 0;
	ck = NULL;
	zone = NULL;
	add_zone(&zone, 16);
	assert_ptr_not_equal(zone, NULL);
	assert_ptr_not_equal(zone_2_mem(zone), NULL);
	zone->chunks = NULL;
	assert_ptr_equal(zone->chunks, NULL);
	
	add_chunk(&(zone->chunks), zone_2_mem(zone), ALIGN_SIZE(3000));
	zone->used = ALIGN_SIZE(3000) + sizeof(t_chunk);
	assert_ptr_not_equal(zone->chunks, NULL);
	
	add_chunk(&(zone->chunks), zone_2_mem(zone) + zone->used, ALIGN_SIZE(3000));
	zone->used += ALIGN_SIZE(3000) + sizeof(t_chunk);
	// FIRST PAGE END
	
	add_chunk(&(zone->chunks), zone_2_mem(zone) + zone->used, ALIGN_SIZE(2000));
	zone->used += ALIGN_SIZE(2000) + sizeof(t_chunk);
	zone->chunks->next->next->status = FREE;

	add_chunk(&(zone->chunks), zone_2_mem(zone) + zone->used, ALIGN_SIZE(4000));
	zone->used += ALIGN_SIZE(4000) + sizeof(t_chunk);
	zone->chunks->next->next->next->status = FREE;
	// SECOND PAGE	
	add_chunk(&(zone->chunks), zone_2_mem(zone) + zone->used, ALIGN_SIZE(6000));
	zone->used += ALIGN_SIZE(6000) + sizeof(t_chunk);
	zone->chunks->next->next->next->next->status = FREE;
	
	add_chunk(&(zone->chunks), zone_2_mem(zone) + zone->used, ALIGN_SIZE(6000));
	zone->used += ALIGN_SIZE(6000) + sizeof(t_chunk);
	
	add_chunk(&(zone->chunks), zone_2_mem(zone) + zone->used, ALIGN_SIZE(6000));
	zone->used += ALIGN_SIZE(6000) + sizeof(t_chunk);
	
	assert_int_equal(cnt_chunks(&(zone->chunks), USED), 4);
	assert_int_equal(cnt_chunks(&(zone->chunks), FREE), 3);
	page_free(&zone, zone->pages_nbr);
	assert_int_equal(cnt_chunks(&(zone->chunks), USED), 4);
	assert_int_equal(cnt_chunks(&(zone->chunks), FREE), 1);
	assert_int_equal(zone->state[2], FREE);

}

void	test_page_free_Page1ToFree(void **state)
{
	t_zone *zone;
	t_chunk *ck;
	int i;

	i = 0;
	ck = NULL;
	zone = NULL;
	add_zone(&zone, 16);
	assert_ptr_not_equal(zone, NULL);
	assert_ptr_not_equal(zone_2_mem(zone), NULL);
	zone->chunks = NULL;
	assert_ptr_equal(zone->chunks, NULL);
	
	add_chunk(&(zone->chunks), zone_2_mem(zone), ALIGN_SIZE(3000));
	zone->used = ALIGN_SIZE(3000) + sizeof(t_chunk);
	assert_ptr_not_equal(zone->chunks, NULL);
	
	add_chunk(&(zone->chunks), zone_2_mem(zone) + zone->used, ALIGN_SIZE(3000));
	zone->used += ALIGN_SIZE(3000) + sizeof(t_chunk);
	zone->chunks->next->status = FREE;
	// FIRST PAGE END
	
	add_chunk(&(zone->chunks), zone_2_mem(zone) + zone->used, ALIGN_SIZE(2000));
	zone->used += ALIGN_SIZE(2000) + sizeof(t_chunk);
	zone->chunks->next->next->status = FREE;

	add_chunk(&(zone->chunks), zone_2_mem(zone) + zone->used, ALIGN_SIZE(4000));
	zone->used += ALIGN_SIZE(4000) + sizeof(t_chunk);
	zone->chunks->next->next->next->status = FREE;
	// SECOND PAGE	
	add_chunk(&(zone->chunks), zone_2_mem(zone) + zone->used, ALIGN_SIZE(6000));
	zone->used += ALIGN_SIZE(6000) + sizeof(t_chunk);
	zone->chunks->next->next->next->next->status = FREE;
	
	add_chunk(&(zone->chunks), zone_2_mem(zone) + zone->used, ALIGN_SIZE(6000));
	zone->used += ALIGN_SIZE(6000) + sizeof(t_chunk);
	
	add_chunk(&(zone->chunks), zone_2_mem(zone) + zone->used, ALIGN_SIZE(6000));
	zone->used += ALIGN_SIZE(6000) + sizeof(t_chunk);
	
	assert_int_equal(cnt_chunks(&(zone->chunks), USED), 3);
	assert_int_equal(cnt_chunks(&(zone->chunks), FREE), 4);
	page_free(&zone, zone->pages_nbr);
	assert_int_equal(cnt_chunks(&(zone->chunks), USED), 3);
	assert_int_equal(cnt_chunks(&(zone->chunks), FREE), 1);
	assert_int_equal(zone->state[1], FREE);
}

void	test_page_free_Page0ToFree(void **state)
{
	t_zone *zone;
	t_chunk *ck;
	int i;

	i = 0;
	ck = NULL;
	zone = NULL;
	add_zone(&zone, 16);
	assert_ptr_not_equal(zone, NULL);
	assert_ptr_not_equal(zone_2_mem(zone), NULL);
	zone->chunks = NULL;
	assert_ptr_equal(zone->chunks, NULL);
	
	add_chunk(&(zone->chunks), zone_2_mem(zone), ALIGN_SIZE(3000));
	zone->used = ALIGN_SIZE(3000) + sizeof(t_chunk);
	assert_ptr_not_equal(zone->chunks, NULL);
	zone->chunks->status = FREE;
	
	add_chunk(&(zone->chunks), zone_2_mem(zone) + zone->used, ALIGN_SIZE(3000));
	zone->used += ALIGN_SIZE(3000) + sizeof(t_chunk);
	zone->chunks->next->status = FREE;
	
	add_chunk(&(zone->chunks), zone_2_mem(zone) + zone->used, ALIGN_SIZE(4096));
	zone->used += ALIGN_SIZE(4096) + sizeof(t_chunk);
	
	add_chunk(&(zone->chunks), zone_2_mem(zone) + zone->used, ALIGN_SIZE(4000));
	zone->used += ALIGN_SIZE(4000) + sizeof(t_chunk);
	
	add_chunk(&(zone->chunks), zone_2_mem(zone) + zone->used, ALIGN_SIZE(6000));
	zone->used += ALIGN_SIZE(6000) + sizeof(t_chunk);
	
	assert_int_equal(cnt_chunks(&(zone->chunks), USED), 3);
	assert_int_equal(cnt_chunks(&(zone->chunks), FREE), 2);
	page_free(&zone, zone->pages_nbr);
	assert_int_equal(cnt_chunks(&(zone->chunks), USED), 3);
	assert_int_equal(cnt_chunks(&(zone->chunks), FREE), 0);
	assert_int_equal(zone->state[0], FREE);
}

void	test_page_free_0pageFree(void **state)
{
	t_zone *zone;
	t_chunk *ck;
	int i;

	i = 0;
	ck = NULL;
	zone = NULL;
	add_zone(&zone, 16);
	assert_ptr_not_equal(zone, NULL);
	assert_ptr_not_equal(zone_2_mem(zone), NULL);
	zone->chunks = NULL;
	assert_ptr_equal(zone->chunks, NULL);
	add_chunk(&(zone->chunks), zone_2_mem(zone), ALIGN_SIZE(4000));
	zone->used = ALIGN_SIZE(4000) + sizeof(t_chunk);
	assert_ptr_not_equal(zone->chunks, NULL);
	add_chunk(&(zone->chunks), zone_2_mem(zone) + zone->used, ALIGN_SIZE(3000));
	zone->used += ALIGN_SIZE(3000) + sizeof(t_chunk);
	add_chunk(&(zone->chunks), zone_2_mem(zone) + zone->used, ALIGN_SIZE(4096));
	zone->used += ALIGN_SIZE(4096) + sizeof(t_chunk);
	add_chunk(&(zone->chunks), zone_2_mem(zone) + zone->used, ALIGN_SIZE(4000));
	zone->used += ALIGN_SIZE(4000) + sizeof(t_chunk);
	add_chunk(&(zone->chunks), zone_2_mem(zone) + zone->used, ALIGN_SIZE(6000));
	zone->used += ALIGN_SIZE(6000) + sizeof(t_chunk);
	assert_int_equal(cnt_chunks(&(zone->chunks), USED), 5);
	page_free(&zone, zone->pages_nbr);
	assert_int_equal(cnt_chunks(&(zone->chunks), USED), 5);
	while (i < 16)
	{
		assert_int_equal(zone->state[i], USED);
		i++;
	}
	
}

