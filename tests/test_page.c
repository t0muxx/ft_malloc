/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_page.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaraval <tmaraval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/01 15:24:03 by tmaraval          #+#    #+#             */
/*   Updated: 2019/10/09 18:08:41 by tmaraval         ###   ########.fr       */
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
	page_free(&zone);
}

/*
          +---+----------------------+---+
          |Z  |                      |   |     P.0
          |H  |       3016 USED      | 20|
          |DR |                      |   |
0x1000    +---+-+--------------------+---+
          |     |                        |
          |00   |     3016 FREE          |   P.1
          |USED |                        |
          +-----+------------------------+
          |                              |
          |    4096 USED                 |  P.2
          |                              |
          +------------------------------+
          |                              |
          |    4096 USED                 |    P.3
          |                              |
          +------------------------------+
*/
void	test_page_free_Page1NoFree(void **state)
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
	
	add_chunk(&(zone->chunks), zone_2_mem(zone), 3016 - sizeof(t_chunk));
	zone->used = 3016;
	assert_ptr_not_equal(zone->chunks, NULL);
	assert_ptr_equal((void *)zone_2_mem(zone), (void *)zone->chunks);
	
	add_chunk(&(zone->chunks), zone_2_mem(zone) + zone->used, 2000 - sizeof(t_chunk));
	zone->used += 2000;
	assert_ptr_equal((void *)zone_2_mem(zone) + 3016, (void *)zone->chunks->next);

	add_chunk(&(zone->chunks), zone_2_mem(zone) + zone->used, 3096 - sizeof(t_chunk));
	zone->used += 3096;
	assert_ptr_equal((void *)zone_2_mem(zone) + 3016 + 2000, (void *)zone->chunks->next->next);
	zone->chunks->next->next->status = FREE;

	add_chunk(&(zone->chunks), zone_2_mem(zone) + zone->used, ALIGN_SIZE(4096) - sizeof(t_chunk));
	zone->used += ALIGN_SIZE(4096);
	assert_ptr_equal((void *)zone + 0x2000, (void *)zone->chunks->next->next->next);
	
	add_chunk(&(zone->chunks), zone_2_mem(zone) + zone->used, 4096 - sizeof(t_chunk));
	zone->used += 4096;
	assert_ptr_equal((void *)zone + 0x3000, (void *)zone->chunks->next->next->next->next);

	print_chunks(zone->chunks, "La : ");	
	assert_int_equal(cnt_chunks(&(zone->chunks), USED), 4);
	assert_int_equal(cnt_chunks(&(zone->chunks), FREE), 1);
	page_free(&zone);
	assert_int_equal(cnt_chunks(&(zone->chunks), FREE), 1);
	assert_int_equal(cnt_chunks(&(zone->chunks), USED), 4);
	assert_int_equal(zone->state[1], USED);
}


/*
          +---+--------------------------+
          |Z  |                          |     P.0
          |H  |       4016 USED          |
          |DR |                          |
0x1000    +---+--------------------------+
          |                              |
          |      4096 FREE               |   P.1
          |                              |
          +------------------------------+
          |                              |
          |    4096 USED                 |  P.2
          |                              |
          +------------------------------+
          |                              |
          |    4096 USED                 |    P.3
          |                              |
          +------------------------------+
*/
void	test_page_free_Page1AlignedToFree(void **state)
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
	
	add_chunk(&(zone->chunks), zone_2_mem(zone), ALIGN_SIZE(4016) - sizeof(t_chunk));
	zone->used = ALIGN_SIZE(4016);
	assert_ptr_not_equal(zone->chunks, NULL);
	assert_ptr_equal((void *)zone_2_mem(zone), (void *)zone->chunks);
	
	add_chunk(&(zone->chunks), zone_2_mem(zone) + zone->used, ALIGN_SIZE(4096) - sizeof(t_chunk));
	zone->used += ALIGN_SIZE(4096);
	assert_ptr_equal((void *)zone + 0x1000, (void *)zone->chunks->next);
	zone->chunks->next->status = FREE;

	add_chunk(&(zone->chunks), zone_2_mem(zone) + zone->used, ALIGN_SIZE(4096) - sizeof(t_chunk));
	zone->used += ALIGN_SIZE(4096);
	assert_ptr_equal((void *)zone + 0x2000, (void *)zone->chunks->next->next);

	add_chunk(&(zone->chunks), zone_2_mem(zone) + zone->used, ALIGN_SIZE(4096) - sizeof(t_chunk));
	zone->used += ALIGN_SIZE(4096);
	assert_ptr_equal((void *)zone + 0x3000, (void *)zone->chunks->next->next->next);

	print_chunks(zone->chunks, "La : ");	
	assert_int_equal(cnt_chunks(&(zone->chunks), USED), 3);
	assert_int_equal(cnt_chunks(&(zone->chunks), FREE), 1);
	page_free(&zone);
	assert_int_equal(cnt_chunks(&(zone->chunks), FREE), 0);
	assert_int_equal(cnt_chunks(&(zone->chunks), USED), 3);
	assert_int_equal(zone->state[1], FREE);
	
}

void	test_page_free_Page1and2ToFree(void **state)
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
	print_chunks(zone->chunks, "after test : ");
	page_free(&zone);
	assert_int_equal(cnt_chunks(&(zone->chunks), USED), 3);
	assert_int_equal(cnt_chunks(&(zone->chunks), FREE), 1);
	assert_int_equal(zone->state[1], FREE);
	assert_int_equal(zone->state[2], FREE);
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
	page_free(&zone);
	assert_int_equal(cnt_chunks(&(zone->chunks), USED), 3);
	assert_int_equal(cnt_chunks(&(zone->chunks), FREE), 2);
	assert_int_equal(zone->state[0], FREE);
	zone->chunks->next->next->status = FREE;
	zone->chunks->next->next->next->status = FREE;
	zone->chunks->next->next->next->next->status = FREE;
	assert_int_equal(cnt_chunks(&(zone->chunks), USED), 0);
	assert_int_equal(cnt_chunks(&(zone->chunks), FREE), 5);
	page_free(&zone);
	assert_int_equal(zone->state[1], FREE);
	assert_int_equal(zone->state[2], FREE);
	assert_int_equal(zone->state[3], FREE);
	assert_int_equal(zone->state[4], FREE);
	add_zone(&zone, 16);
	assert_int_equal(cnt_zone(zone), 2);
	print_zones(zone, "WIWIWIWIWIWIWIW");
	munmap_small_medium(&zone);
	assert_int_equal(cnt_zone(zone), 1);
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
	page_free(&zone);
	assert_int_equal(cnt_chunks(&(zone->chunks), USED), 5);
	while (i < 16)
	{
		assert_int_equal(zone->state[i], USED);
		i++;
	}
	
}

