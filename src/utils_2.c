/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaraval <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 12:10:25 by tmaraval          #+#    #+#             */
/*   Updated: 2019/10/17 12:10:53 by tmaraval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

void	init_opt(unsigned long *opt)
{
	if (!(*opt & OPT_SET))
		*opt |= 1UL << 10;
	if (getenv("DEBUG_FREE"))
		*opt |= 1UL << 0;
	if (getenv("DEBUG_FREE_MEM"))
		*opt |= 1UL << 1;
	if (getenv("DEBUG_MALLOC"))
		*opt |= 1UL << 2;
	if (getenv("DEBUG_MALLOC_RET"))
		*opt |= 1UL << 3;
	if (getenv("DEBUG_CALLOC"))
		*opt |= 1UL << 4;
	if (getenv("DEBUG_CALLOC_RET"))
		*opt |= 1UL << 5;
	if (getenv("DEBUG_REALLOC"))
		*opt |= 1UL << 6;
	if (getenv("DEBUG_REALLOC_RET"))
		*opt |= 1UL << 7;
	if (getenv("DEBUG_MUNMAP"))
		*opt |= 1UL << 8;
	if (getenv("DEBUG_MMAP"))
		*opt |= 1UL << 9;
}
