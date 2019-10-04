/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaraval <tmaraval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/24 16:21:20 by tmaraval          #+#    #+#             */
/*   Updated: 2019/10/04 18:05:07 by tmaraval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_malloc.h"
#include "tests.h"
#include <cmocka.h>

int main(void)
{
	const struct CMUnitTest tests[] = {
        /*
		cmocka_unit_test(test_add_zone_large),
		cmocka_unit_test(test_add_zone_null),
        cmocka_unit_test(test_add_zone_after),
        cmocka_unit_test(test_search_zone_same),
        cmocka_unit_test(test_search_zone_needAdd),
        cmocka_unit_test(test_should_delete_zone),
        cmocka_unit_test(test_page_free_Page0ToFree),
		cmocka_unit_test(test_page_free_Page1ToFree),
		cmocka_unit_test(test_page_free_Page2ToFree),
		cmocka_unit_test(test_page_free_Page16ToFree),
		cmocka_unit_test(test_malloc_simple),
		cmocka_unit_test(test_malloc_multiple),
        cmocka_unit_test(test_delete_zone),*/
        cmocka_unit_test(test_page_free_0pageFree),
    };
	printf("sizeof(t_zone) = %lu\n", sizeof(t_zone));
	printf("sizeof(t_zone) = %lu\n", ALIGN_SIZE(sizeof(t_zone)));
	printf("|DEBUG| -> pagesize = %d\n", getpagesize());
    return cmocka_run_group_tests(tests, NULL, NULL);
}

