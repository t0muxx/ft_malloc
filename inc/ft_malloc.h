/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaraval <tmaraval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/24 14:57:13 by tmaraval          #+#    #+#             */
/*   Updated: 2019/09/27 10:52:30 by tmaraval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MALLOC_H
# define FT_MALLOC_H

# include <stdio.h>
# include <sys/mman.h>
# include <stddef.h>
# include <libft.h>
# include <errno.h>
# include <unistd.h>

# define ALIGN 16
# define MULTIPLE_ZONE_TINY 16
# define MULTIPLE_ZONE_MEDIUM 32
//#define SZ_MEDIUM ((SZ_ZONE_MEDIUM/100)-sizeof(struct s_chunk))+(ALIGN-((SZ_ZONE_MEDIUM/100)-sizeof(struct s_chunk))%16)

# define DEBUG 1
//# define DEBUG_CHUNK 1
# define DEBUG_ZONE 1
//#define DEBUG_FREE 1
// Check norm
# define ALIGN_SIZE(x) (x + ALIGN - (x%ALIGN))

enum e_status {
	USED,
	FREE
};

// s_chunk->prev used for alignment

typedef struct	s_chunk
{
	size_t status;
	size_t size;
	struct s_chunk *prev;
	struct s_chunk *next;

}				t_chunk;

typedef struct	s_zone
{
	size_t			size;
	size_t			used;
	t_chunk			*chunks;
	struct s_zone	*next;

}				t_zone;

typedef struct	s_size
{
	size_t  sz_zone_tiny;
	size_t  sz_min_alloc_tiny;
	size_t  sz_zone_medium;
	size_t  sz_min_alloc_medium;
	size_t	sz_tiny;
	size_t  sz_medium;

}				t_size;

typedef struct	s_malloc
{
	t_zone			*zone_tiny;
	struct s_size	*size;

}				t_malloc;

extern t_malloc g_malloc;

void	*ft_malloc(size_t size);
int		init_malloc();
void	ft_free(void *ptr);
void	*zone_2_mem(t_zone *zone);
int		add_zone(t_zone **zone, size_t size);
void	*search_zone(t_zone **zone, size_t size, size_t sz_zone);
int		have_free_chunk(t_chunk **head);
void	remove_free_chunk(t_chunk **head);
int		zone_need_free(t_zone **zone, size_t size_alloc_min);
int		remove_zone(t_zone **zone, size_t size_alloc_min);

//DEBUG : 
void	print_chunks(t_chunk *chunk, char * chunk_name);
void	print_zones(t_zone *zone, char *zone_name);
#endif
