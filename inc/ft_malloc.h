/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaraval <tmaraval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/24 14:57:13 by tmaraval          #+#    #+#             */
/*   Updated: 2019/10/03 18:22:15 by tmaraval         ###   ########.fr       */
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
# define DEBUG 0
//# define DEBUG_CHUNK 1
//# define DEBUG_ZONE 1
//# define DEBUG_FREE 1
//# define DEBUG_PAGE 1
# define ALIGN_SIZE(x) (x + ALIGN - (x%ALIGN))

enum			e_status {
	USED,
	FREE
};

typedef struct	s_chunk
{
	size_t			status;
	size_t			size;
	struct s_chunk	*prev;
	struct s_chunk	*next;

}				t_chunk;

typedef struct	s_zone
{
	size_t			size;
	size_t			used;
	t_chunk			*chunks;
	int				pages_nbr;
	char			state[MULTIPLE_ZONE_MEDIUM];
	struct s_zone	*next;

}				t_zone;

typedef struct	s_malloc
{
	t_zone			*zone_tiny;
	t_zone			*zone_medium;

}				t_malloc;

t_malloc g_malloc_state;

/*
** Front fucntion 
*/
void	*ft_malloc(size_t size);
void	ft_free(void *ptr);

/*
** INIT :
*/
int		init_malloc();

/*
** ZONE :
*/
void	*zone_2_mem(t_zone *zone);
t_zone	*mem_2_zone(void *mem);
int		add_zone(t_zone **zone, size_t pages_nbr);
t_zone	*search_zone(t_zone **zone, size_t size);
int		zone_need_free(t_zone **zone, size_t size_alloc_min);
void	remove_zone(t_zone **zone, size_t size_alloc_min);
int		cnt_zone(t_zone *zone);
int		should_delete_zone(t_zone *zone);
void	delete_zone(t_zone **zone, t_zone **del);

/*
** PAGE :
*/
void	page_free(t_zone **current_zone, size_t pages_nbr);
void	page_free_remove_chunk_and_munmap(
		t_zone **current_zone, t_chunk **chunk, void *base, int p);
int		page_free_check_chunk_state_for_page(t_chunk **chunk, void *base, int p);
void	page_free_check_chunk(t_zone **current_zone, t_chunk **chunk,
								void *base, int p);
void	page_free(t_zone **current_zone, size_t pages_nbr);
t_chunk *page_free_find_chunk_left_border(t_chunk *chunk, void *base, int p);

/* 
** CHUNKS :  
*/
int		have_free_chunk(t_chunk **head);
int		search_chunk(t_chunk *chunk);
void	remove_free_chunk(t_chunk **head);
void	munmap_small_medium(t_zone **zone);
int		have_free_chunk(t_chunk **head);
void	add_chunk(t_chunk **head, void *zone_base, size_t sz_aligned);
void	delete_chunk(t_chunk **head, t_chunk *toDelete);
void 	*search_free_chunk(t_zone *head, size_t sz_aligned);

size_t	size_max(size_t multiple);

//DEBUG : 
void	print_chunks(t_chunk *chunk, char *chunk_name);
void	print_zones(t_zone *zone, char *zone_name);
void	print_chunk(t_chunk *tmp);
#endif
