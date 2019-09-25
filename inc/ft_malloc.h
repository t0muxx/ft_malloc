/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaraval <tmaraval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/24 14:57:13 by tmaraval          #+#    #+#             */
/*   Updated: 2019/09/25 11:36:45 by tmaraval         ###   ########.fr       */
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
#define ALIGN_SIZE(x) (x + ALIGN - (x%ALIGN))

enum e_status {
	USED,
	FREE
};

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
	t_zone	*zone_tiny;
	t_chunk *chunk_tiny;

}				t_malloc;

extern t_malloc g_malloc;

void	*ft_malloc(size_t size);
int		init_malloc(t_malloc *g_malloc);
void	print_chunks(t_chunk *chunk, char * chunk_name);
void	ft_free(void *ptr);
