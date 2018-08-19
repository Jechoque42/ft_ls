/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jechoque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/22 15:17:02 by jechoque          #+#    #+#             */
/*   Updated: 2017/12/01 18:52:34 by jechoque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "../libft/libft.h"
# include <stdarg.h>

/*
**------------------------DEFINE COLOR && LENGTH && BUFFER---------------------
*/

# define BLUE			"\033[34m"
# define EOC			"\033[0m"
# define RED			"\033[31m"
# define CYAN			"\033[36m"
# define GREEN			"\033[32m"
# define YELLOW			"\033[33m"
# define PURPLE			"\033[35m"

# define HH				'i'
# define LL 			'm'

# define BUFF_SIZE_PF	4096

/*
**------------------------------FLAG STRUCTURE---------------------------------
*/

typedef struct	s_flag
{
	char		buffer[BUFF_SIZE_PF];
	int			i;
	char		*pref;
	char		type;
	char		lgth;
	int			plus;
	int			minu;
	int			dies;
	int			spac;
	int			zero;
	int			wdth;
	ssize_t		prec;
	ssize_t		len;
}				t_flag;

/*
**------------------------------FUNCTION POINTER--------------------------------
*/

typedef ssize_t	(*t_handler)(const char, va_list*, t_flag*);
t_handler		ft_get_handler(char c);

/*
**------------------------------PARSER UTILITY----------------------------------
*/

int				ft_isflag(int c);
int				ft_islength(int c);
int				ft_istype(int c);
ssize_t			ft_getflag(t_flag *fg, const char *format, va_list *arr);
ssize_t			ft_get_color(const char *format, t_flag *fg);

/*
**-------------------------------BUFFER UTILITY---------------------------------
*/

int				ft_check_buffer(t_flag *fg);
void			ft_buffnwstr(const wchar_t *str, size_t len, t_flag *fg);
void			ft_buffnstr(const char *str, int len, t_flag *fg);
void			ft_buffwchar(wchar_t c, t_flag *fg);
void			ft_buffpad(int width, ssize_t len, char pad, t_flag *fg);
void			ft_buffbase(const char c, uintmax_t n, unsigned int base,
				t_flag *fg);

/*
**------------------------------CONVERSION FUNCTIONS----------------------------
*/

uintmax_t		ft_length_ucast(va_list *arr, t_flag *fg);

ssize_t			ft_printf_str(const char c, va_list *arr, t_flag *fg);
ssize_t			ft_printf_wstr(const char c, va_list *arr, t_flag *fg);
ssize_t			ft_printf_char(const char c, va_list *arr, t_flag *fg);
ssize_t			ft_printf_wchar(const char c, va_list *arr, t_flag *fg);
ssize_t			ft_printf_sign(const char c, va_list *arr, t_flag *fg);
ssize_t			ft_printf_int(const char c, va_list *arr, t_flag *fg);
ssize_t			ft_printf_ptr(const char c, va_list *arr, t_flag *fg);
ssize_t			ft_printf_octal(const char c, va_list *arr, t_flag *fg);
ssize_t			ft_printf_uint(const char c, va_list *arr, t_flag *fg);
ssize_t			ft_printf_hexa(const char c, va_list *arr, t_flag *fg);
ssize_t			ft_printf_binary(const char c, va_list *arr, t_flag *fg);
ssize_t			ft_printf_float(const char c, va_list *arr, t_flag *fg);
ssize_t			ft_printf_sgeneric(const char c, intmax_t nbr, t_flag *fg);
ssize_t			ft_printf_ugeneric(const char c, uintmax_t nbr, t_flag *fg,
				int base);

/*
**----------------------------------FT_PRINTF-----------------------------------
*/

int				ft_printf(const char *format, ...);

#endif
