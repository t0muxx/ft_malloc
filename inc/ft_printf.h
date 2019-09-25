/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaraval <tmaraval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/09 13:34:47 by tmaraval          #+#    #+#             */
/*   Updated: 2019/09/24 16:38:21 by t0mux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <stdio.h>
# include <unistd.h>
# include <limits.h>
# include "libft.h"
# include <stdlib.h>
# include <stdio.h>
# include <wchar.h>

# define TRUE 1
# define FALSE 0

# ifdef __linux__
#  include <inttypes.h>
# endif

# define INTMAX_T intmax_t
# define UINTMAX_T uintmax_t

# define AVAILABLE_FLAG "#0- +"
# define FLG_SHARP 1
# define FLG_ZERO 2
# define FLG_MINUS 4
# define FLG_SP 8
# define FLG_PLUS 16

# define AVAILABLE_LENMOD "hljz"
# define LENMOD_H	1
# define LENMOD_HH	2
# define LENMOD_L	4
# define LENMOD_LL	8
# define LENMOD_J	16
# define LENMOD_Z	32

# define AVAILABLE_CONV "sSpcCoOxXdDiuU%"

typedef	struct	s_parsed_opt
{
	int				bin_flag;
	int				in_width;
	int				in_precision;
	int				bin_lenmod;
	char			ch_convert;
	int				in_argnbr;
	char			*str_arg;
	wchar_t			*wstr_arg;
	int				in_base;
	char			ch_ch;
}				t_parsed_opt;

int				ft_printf(const char *restrict format, ...);

void			ft_parser_init_t_parsed_opt(t_parsed_opt *opt);
int				ft_parser(t_parsed_opt *opt, char **format, va_list curr_arg);
int				ft_parser_managepercent(char **format);
int				ft_parser_read_int_upd_str(char **format);
void			ft_parser_manage_argnbr(char **format, char *begin,
															t_parsed_opt *opt);
void			ft_parser_manage_flag(char **format, t_parsed_opt *opt);
void			ft_parser_manage_width(char **format, t_parsed_opt *opt);
void			ft_parser_manage_prec(char **format, t_parsed_opt *opt);
void			ft_parser_do_parse(t_parsed_opt *opt, char *begin,
																char **format);
int				ft_parser_manage_lenmod(char **format, t_parsed_opt *opt);
int				ft_parser_read_int_upd_str(char **format);
int				ft_conv(t_parsed_opt *opt, va_list curr_arg, char **format);
int				ft_conv_integer(t_parsed_opt *opt, va_list curr_arg);
void			ft_conv_int_arg(t_parsed_opt *opt, va_list curr_arg);
int				ft_conv_int_arg_wlenmod(t_parsed_opt *opt, va_list curr_arg);
void			ft_conv_char(t_parsed_opt *opt, va_list curr_arg);
void			ft_conv_str(t_parsed_opt *opt, va_list curr_arg);
void			ft_printf_precision(t_parsed_opt *opt);
void			ft_printf_str_precision(t_parsed_opt *opt);
void			ft_printf_wcstr_precision(t_parsed_opt *opt);
void			ft_printf_width(t_parsed_opt *opt);
void			ft_printf_width_do(t_parsed_opt *opt);
void			ft_printf_cwidth(t_parsed_opt *opt);
void			ft_printf_wcstr_width(t_parsed_opt *opt);
void			ft_printf_num_manage_flag(t_parsed_opt *opt);
int				ft_printf_flag_strarg_isnega(t_parsed_opt *opt);
void			ft_printf_num_sharp(t_parsed_opt *opt);

char			*ft_lltoa_base(long long nb, int base);
char			*ft_ulltoa_base(unsigned long long nb, int base);
char			*ft_sitoa_base(short int nb, int base);
void			ft_printf_print_opt(t_parsed_opt opt);
#endif
