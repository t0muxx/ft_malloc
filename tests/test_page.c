/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_page.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaraval <tmaraval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/01 15:24:03 by tmaraval          #+#    #+#             */
/*   Updated: 2019/10/10 14:56:54 by tmaraval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"
#include "tests.h"

/*
  base  +--+------------------+--+
        |H |     3016 FREE    |  |
        |D |                  |20|     P.0
        |RZ|                  |FR|
+0x1000 +------------+-----------+
        |  |1508     | 1308   |  |
        |00|FREE     | FREE   |12|    P.1
        |EE|         |        |  |
        +-----+------+--------+--+
        |     |  3096 USED       |
        |00   |                  |   P.2
        |FREE |                  |
        +-----+------------------+
        |                        |
        |4096 USED               |  P.3
        |                        |
        +------------------------|
*/

void test_page_free_Page0And1ToFree(void **state)
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
	zone->chunks->status = FREE;

	add_chunk(&(zone->chunks), zone_2_mem(zone) + zone->used, 2000 - sizeof(t_chunk));
	zone->used += 2000;
	assert_ptr_equal((void *)zone_2_mem(zone) + 3016, (void *)zone->chunks->next);
	zone->chunks->next->status = FREE;

	add_chunk(&(zone->chunks), zone_2_mem(zone) + zone->used, 1548 - sizeof(t_chunk));
	zone->used += 1548;
	assert_ptr_equal((void *)zone_2_mem(zone) + 3016 + 2000, (void *)zone->chunks->next->next);
	zone->chunks->next->next->status = FREE;
	
	add_chunk(&(zone->chunks), zone_2_mem(zone) + zone->used, 1348 - sizeof(t_chunk));
	zone->used += 1348;
	assert_ptr_equal((void *)zone_2_mem(zone) + 3016 + 1548 + 2000,
			(void *)zone->chunks->next->next->next);
	zone->chunks->next->next->next->status = FREE;
	
	add_chunk(&(zone->chunks), zone_2_mem(zone) + zone->used, 1200 - sizeof(t_chunk));
	zone->used += 1200;
	assert_ptr_equal((void *)zone_2_mem(zone) + 3016 + 1548 + 2000 + 1348,
			(void *)zone->chunks->next->next->next->next);
	zone->chunks->next->next->next->next->status = FREE;

	add_chunk(&(zone->chunks), zone_2_mem(zone) + zone->used, 3096 - sizeof(t_chunk));
	zone->used += 3096;
	assert_ptr_equal((void *)zone + 0x2000 + 1000, (void *)zone->chunks->next->next->next->next->next);
	
	add_chunk(&(zone->chunks), zone_2_mem(zone) + zone->used, 4096 - sizeof(t_chunk));
	zone->used += 4096;
	assert_ptr_equal((void *)zone + 0x3000, (void *)zone->chunks->next->next->next->next->next->next);

	print_chunks(zone->chunks, "La : ");	
	assert_int_equal(cnt_chunks(&(zone->chunks), USED), 2);
	assert_int_equal(cnt_chunks(&(zone->chunks), FREE), 5);
	page_free(&zone);
	assert_int_equal(cnt_chunks(&(zone->chunks), FREE), 1);
	assert_int_equal(cnt_chunks(&(zone->chunks), USED), 2);
	assert_int_equal(zone->state[1], FREE);
	assert_int_equal(zone->state[0], USED);
}


/*
  base  +--+------------------+--+
        |H |     3016 USED    |  |
        |D |                  |20|     P.0
        |RZ|                  |FR|
+0x1000 +------------+-----------+
        |  |1548     | 1348   |  |
        |00|FREE     | FREE   |12|    P.1
        |EE|         |        |  |
        +-----+------+--------+--+
        |     |  3096 FREE       |
        |00   |                  |   P.2
        |FREE |                  |
        +-----+------------------+
        |                        |
        |4096 USED               |  P.3
        |                        |
        +------------------------|
*/
void test_page_free_Page1ManyAnd2ManyToFree(void  **state)
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
	zone->chunks->next->status = FREE;

	add_chunk(&(zone->chunks), zone_2_mem(zone) + zone->used, 1548 - sizeof(t_chunk));
	zone->used += 1548;
	assert_ptr_equal((void *)zone_2_mem(zone) + 3016 + 2000, (void *)zone->chunks->next->next);
	zone->chunks->next->next->status = FREE;
	
	add_chunk(&(zone->chunks), zone_2_mem(zone) + zone->used, 1348 - sizeof(t_chunk));
	zone->used += 1348;
	assert_ptr_equal((void *)zone_2_mem(zone) + 3016 + 1548 + 2000,
			(void *)zone->chunks->next->next->next);
	zone->chunks->next->next->next->status = FREE;
	
	add_chunk(&(zone->chunks), zone_2_mem(zone) + zone->used, 1200 - sizeof(t_chunk));
	zone->used += 1200;
	assert_ptr_equal((void *)zone_2_mem(zone) + 3016 + 1548 + 2000 + 1348,
			(void *)zone->chunks->next->next->next->next);
	zone->chunks->next->next->next->next->status = FREE;

	add_chunk(&(zone->chunks), zone_2_mem(zone) + zone->used, 3096 - sizeof(t_chunk));
	zone->used += 3096;
	assert_ptr_equal((void *)zone + 0x2000 + 1000, (void *)zone->chunks->next->next->next->next->next);
	zone->chunks->next->next->next->next->next->status = FREE;
	
	add_chunk(&(zone->chunks), zone_2_mem(zone) + zone->used, 4096 - sizeof(t_chunk));
	zone->used += 4096;
	assert_ptr_equal((void *)zone + 0x3000, (void *)zone->chunks->next->next->next->next->next->next);

	print_chunks(zone->chunks, "La : ");	
	assert_int_equal(cnt_chunks(&(zone->chunks), USED), 2);
	assert_int_equal(cnt_chunks(&(zone->chunks), FREE), 5);
	page_free(&zone);
	assert_int_equal(cnt_chunks(&(zone->chunks), FREE), 0);
	assert_int_equal(cnt_chunks(&(zone->chunks), USED), 2);
	assert_int_equal(zone->state[1], FREE);
	assert_int_equal(zone->state[2], FREE);

}

/*
  base  +--+------------------+--+
        |H |     3016 USED    |  |
        |D |                  |20|     P.0
        |RZ|                  |FR|
+0x1000 +------------+-----------+
        |  |1508     |   1508    |
        |00|FREE     |   FREE    |    P.1
        |EE|         |           |
        +------------+-----------+
        |                        |
        |4096 FREE               |   P.2
        |                        |
        +------------------------+
        |                        |
        |4096 USED               |  P.3
        |                        |
        +------------------------|
*/
void	test_page_free_Page1ManyAnd2ToFree(void **state)
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
	zone->chunks->next->status = FREE;

	add_chunk(&(zone->chunks), zone_2_mem(zone) + zone->used, 1548 - sizeof(t_chunk));
	zone->used += 1548;
	assert_ptr_equal((void *)zone_2_mem(zone) + 3016 + 2000, (void *)zone->chunks->next->next);
	zone->chunks->next->next->status = FREE;
	
	add_chunk(&(zone->chunks), zone_2_mem(zone) + zone->used, 1548 - sizeof(t_chunk));
	zone->used += 1548;
	assert_ptr_equal((void *)zone_2_mem(zone) + 3016 + 1548 + 2000, (void *)zone->chunks->next->next->next);
	zone->chunks->next->next->next->status = FREE;

	add_chunk(&(zone->chunks), zone_2_mem(zone) + zone->used, ALIGN_SIZE(4096) - sizeof(t_chunk));
	zone->used += ALIGN_SIZE(4096);
	assert_ptr_equal((void *)zone + 0x2000, (void *)zone->chunks->next->next->next->next);
	zone->chunks->next->next->next->next->status = FREE;
	
	add_chunk(&(zone->chunks), zone_2_mem(zone) + zone->used, 4096 - sizeof(t_chunk));
	zone->used += 4096;
	assert_ptr_equal((void *)zone + 0x3000, (void *)zone->chunks->next->next->next->next->next);

	print_chunks(zone->chunks, "La : ");	
	assert_int_equal(cnt_chunks(&(zone->chunks), USED), 2);
	assert_int_equal(cnt_chunks(&(zone->chunks), FREE), 4);
	page_free(&zone);
	assert_int_equal(cnt_chunks(&(zone->chunks), FREE), 0);
	assert_int_equal(cnt_chunks(&(zone->chunks), USED), 2);
	assert_int_equal(zone->state[1], FREE);
	assert_int_equal(zone->state[2], FREE);

}

/*
  base  +--+------------------+--+
        |H |     3016 USED    |  |
        |D |                  |20|     P.0
        |RZ|                  |FR|
+0x1000 +------------+-----------+
        |  |1508     |   1508    |
        |00|FREE     |   FREE    |    P.1
        |EE|         |           |
        +------------+-----------+
        |                        |
        |4096 USED               |   P.2
        |                        |
        +------------------------+
        |                        |
        |4096 USED               |  P.3
        |                        |
        +------------------------|
*/
void	test_page_free_Page1ManyToFree(void **state)
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
	zone->chunks->next->status = FREE;

	add_chunk(&(zone->chunks), zone_2_mem(zone) + zone->used, 1548 - sizeof(t_chunk));
	zone->used += 1548;
	assert_ptr_equal((void *)zone_2_mem(zone) + 3016 + 2000, (void *)zone->chunks->next->next);
	zone->chunks->next->next->status = FREE;
	
	add_chunk(&(zone->chunks), zone_2_mem(zone) + zone->used, 1548 - sizeof(t_chunk));
	zone->used += 1548;
	assert_ptr_equal((void *)zone_2_mem(zone) + 3016 + 1548 + 2000, (void *)zone->chunks->next->next->next);
	zone->chunks->next->next->next->status = FREE;

	printf("zone used = %lu\n", zone->used);
	add_chunk(&(zone->chunks), zone_2_mem(zone) + zone->used, ALIGN_SIZE(4096) - sizeof(t_chunk));
	zone->used += ALIGN_SIZE(4096);
	assert_ptr_equal((void *)zone + 0x2000, (void *)zone->chunks->next->next->next->next);
	
	add_chunk(&(zone->chunks), zone_2_mem(zone) + zone->used, 4096 - sizeof(t_chunk));
	zone->used += 4096;
	assert_ptr_equal((void *)zone + 0x3000, (void *)zone->chunks->next->next->next->next->next);

	print_chunks(zone->chunks, "La : ");	
	assert_int_equal(cnt_chunks(&(zone->chunks), USED), 3);
	assert_int_equal(cnt_chunks(&(zone->chunks), FREE), 3);
	page_free(&zone);
	assert_int_equal(cnt_chunks(&(zone->chunks), FREE), 0);
	assert_int_equal(cnt_chunks(&(zone->chunks), USED), 3);
	assert_int_equal(zone->state[1], FREE);

}
/*
          +---+----------------------+---+
          |Z  |                      |   |     P.0
          |H  |       3016 USED      | 20|
          |DR |                      |   |
0x1000    +---+-+------------------------+
          |     |                    |   |
          |00   |     2096 FREE      |   |   P.1
          |FREE |                    |   |
          +-----+--------------------+---+
          |                              |
          |                              |  P.2
          |                              |
          +------------------------------+
          |                              |
          |                              |    P.3
          |                              |
          +------------------------------+
*/
void	test_page_free_Page1NothingAfterNoFree(void **state)
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
	zone->chunks->next->status = FREE;

	add_chunk(&(zone->chunks), zone_2_mem(zone) + zone->used, 3096 - sizeof(t_chunk));
	zone->used += 3096;
	assert_ptr_equal((void *)zone_2_mem(zone) + 3016 + 2000, (void *)zone->chunks->next->next);
	zone->chunks->next->next->status = FREE;

	print_chunks(zone->chunks, "La : ");	
	assert_int_equal(cnt_chunks(&(zone->chunks), USED), 1);
	assert_int_equal(cnt_chunks(&(zone->chunks), FREE), 2);
	page_free(&zone);
	assert_int_equal(cnt_chunks(&(zone->chunks), FREE), 2);
	assert_int_equal(cnt_chunks(&(zone->chunks), USED), 1);
	assert_int_equal(zone->state[1], USED);
}

/*
          +---+----------------------+---+
          |Z  |                      |   |     P.0
          |H  |       3016 USED      | 20|
          |DR |                      |   |
0x1000    +---+-+--------------------+---+
          |     |                        |
          |00   |     3096 FREE          |   P.1
          |FREE |                        |
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
	
	add_chunk(&(zone->chunks), zone_2_mem(zone), 3016 - sizeof(t_chunk));
	zone->used = 3016;
	assert_ptr_not_equal(zone->chunks, NULL);
	assert_ptr_equal((void *)zone_2_mem(zone), (void *)zone->chunks);
	
	add_chunk(&(zone->chunks), zone_2_mem(zone) + zone->used, 2000 - sizeof(t_chunk));
	zone->used += 2000;
	assert_ptr_equal((void *)zone_2_mem(zone) + 3016, (void *)zone->chunks->next);
	zone->chunks->next->status = FREE;

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
	assert_int_equal(cnt_chunks(&(zone->chunks), USED), 3);
	assert_int_equal(cnt_chunks(&(zone->chunks), FREE), 2);
	page_free(&zone);
	assert_int_equal(cnt_chunks(&(zone->chunks), FREE), 0);
	assert_int_equal(cnt_chunks(&(zone->chunks), USED), 3);
	assert_int_equal(zone->state[1], FREE);

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

