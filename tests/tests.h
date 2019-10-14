#include <assert.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <stdint.h>
#include <cmocka.h>
#include "ft_malloc.h"


void	test_add_zone_after(void **state);
void	test_add_zone_null(void **state);
void	test_add_zone_large(void **state);
void	test_search_zone_same(void **state);
void	test_search_zone_needAdd(void **state);
void	test_page_free_0pageFree(void **state);
void	test_page_free_Page1AlignedToFree(void **state);
void	test_page_free_Page1NoFree(void **state);
void	test_page_free_Page1ToFree(void **state);
void	test_page_free_Page1NothingAfterNoFree(void **state);
void	test_page_free_Page1ManyToFree(void **state);
void	test_page_free_Page1ManyAnd2ToFree(void **state);
void	test_page_free_Page1ManyAnd2ManyToFree(void  **state);
void	test_page_free_Page0And1ToFree(void **state);
void	test_malloc_simple(void **state);
void	test_malloc_multiple(void **state);
void	test_malloc_buggy(void **state);
void	test_malloc_buggy_2(void **state);
void	test_should_delete_zone(void **state);
void	test_delete_zone(void **state);
void	test_shrink_zone_noShrink(void **state);
void	test_shrink_zone_shrink(void **state);
int		cnt_chunks(t_chunk **head, size_t status);
