/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaraval <tmaraval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/24 14:57:13 by tmaraval          #+#    #+#             */
/*   Updated: 2019/09/25 09:39:08 by tmaraval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <sys/mman.h>
#include <stddef.h>
#include <libft.h>
#include <errno.h>

#define ALIGN 16
#define SZ_ZONE_TINY 4096*16
#define SZ_TINY ((SZ_ZONE_TINY/100)-sizeof(struct s_chunk))+(ALIGN-((SZ_ZONE_TINY/100)-sizeof(struct s_chunk))%16)
#define SZ_ZONE_MEDIUM 4096*32
#define SZ_MEDIUM ((SZ_ZONE_MEDIUM/100)-sizeof(struct s_chunk))+(ALIGN-((SZ_ZONE_MEDIUM/100)-sizeof(struct s_chunk))%16)
#define DEBUG 1

#define ZONE2MEM(x) ((void *)x + sizeof(t_zone))

typedef struct	s_zone
{
	size_t	size;
	size_t	used;

}				t_zone;


// s_chunk->prev used for alignment

typedef struct	s_chunk
{
	size_t status;
	size_t size;
	struct s_chunk *prev;
	struct s_chunk *next;

}				t_chunk;

typedef struct	s_malloc
{
	t_zone *zone_tiny;

}				t_malloc;

void	*ft_malloc(size_t size);
int		init_malloc(t_malloc *g_malloc);
