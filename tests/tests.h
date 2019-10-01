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


void test_add_zone_after(void **state);
void test_add_zone_null(void **state);
void test_search_zone_same(void **state);
void test_search_zone_needAdd(void **state);
void test_page_free_0pageFree(void **state);
void test_page_free_firstPageToFree(void **state);
int  cnt_chunks(t_chunk **head, size_t status);
