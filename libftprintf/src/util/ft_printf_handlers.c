/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_handlers.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jechoque <jbchoquet@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/23 23:09:56 by jechoque          #+#    #+#             */
/*   Updated: 2017/12/01 17:28:31 by jechoque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ft_printf.h"

static ssize_t	ft_printf_long(const char c, va_list *arr, t_flag *fg)
{
	fg->lgth = 'l';
	return ((ft_get_handler(c + 32))(c + 32, arr, fg));
}

static ssize_t	ft_printf_n(const char c, va_list *arr, t_flag *fg)
{
	int	*write;

	(void)c;
	write = va_arg(*arr, int*);
	*write = fg->len;
	return (0);
}

static void		ft_config_tab_handlers(t_handler *tab_handlers)
{
	tab_handlers['s'] = &ft_printf_str;
	tab_handlers['S'] = &ft_printf_wstr;
	tab_handlers['c'] = &ft_printf_char;
	tab_handlers['C'] = &ft_printf_wchar;
	tab_handlers['%'] = &ft_printf_sign;
	tab_handlers['d'] = &ft_printf_int;
	tab_handlers['i'] = &ft_printf_int;
	tab_handlers['D'] = &ft_printf_long;
	tab_handlers['O'] = &ft_printf_long;
	tab_handlers['U'] = &ft_printf_long;
	tab_handlers['p'] = &ft_printf_ptr;
	tab_handlers['o'] = &ft_printf_octal;
	tab_handlers['u'] = &ft_printf_uint;
	tab_handlers['x'] = &ft_printf_hexa;
	tab_handlers['X'] = &ft_printf_hexa;
	tab_handlers['b'] = &ft_printf_binary;
	tab_handlers['f'] = &ft_printf_float;
	tab_handlers['F'] = &ft_printf_float;
	tab_handlers['n'] = &ft_printf_n;
}

t_handler		ft_get_handler(char c)
{
	static t_handler	*tab_handlers = NULL;

	if (tab_handlers == NULL)
	{
		if (!(tab_handlers = malloc(sizeof(t_handler) * 256)))
			return (NULL);
		ft_config_tab_handlers(tab_handlers);
	}
	return (tab_handlers[(int)c]);
}
