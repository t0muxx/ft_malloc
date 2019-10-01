/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaraval <tmaraval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/24 16:21:20 by tmaraval          #+#    #+#             */
/*   Updated: 2019/10/01 15:47:28 by tmaraval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_malloc.h"
#include "tests.h"
#include <cmocka.h>

int main(void)
{
	const struct CMUnitTest tests[] = {
        cmocka_unit_test(test_add_zone_null),
        cmocka_unit_test(test_add_zone_after),
        cmocka_unit_test(test_search_zone_same),
        cmocka_unit_test(test_search_zone_needAdd),
        cmocka_unit_test(test_page_free_0pageFree),
        cmocka_unit_test(test_page_free_firstPageToFree),
        cmocka_unit_test(test_page_free_secondPageToFree),
    };

    return cmocka_run_group_tests(tests, NULL, NULL);
}

