/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jechoque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/22 14:53:03 by jechoque          #+#    #+#             */
/*   Updated: 2017/12/01 18:44:24 by jechoque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "ft_printf.h"

static void			ft_init_flag(t_flag *fg)
{
	fg->pref = NULL;
	fg->type = '\0';
	fg->lgth = '\0';
	fg->plus = 0;
	fg->minu = 0;
	fg->dies = 0;
	fg->spac = 0;
	fg->zero = 0;
	fg->wdth = 0;
	fg->prec = -1;
}

static void			ft_printf_vtouffet(const char **format, t_flag *flag)
{
	if (**format == '{')
		*format += ft_get_color(*format, flag);
	ft_check_buffer(flag);
	if (**format && ++flag->len)
		flag->buffer[flag->i++] = *((*format)++);
}

int					ft_printf(const char *format, ...)
{
	va_list		ap;
	t_flag		flag;

	va_start(ap, format);
	flag.len = 0;
	flag.i = 0;
	while (*format)
		if (*format == '%' && *++format)
		{
			ft_init_flag(&flag);
			if (!ft_istype(*format))
				format += ft_getflag(&flag, format, &ap);
			*format ? flag.type = *format++ : 0;
			if (ft_istype(flag.type))
				flag.len += (ft_get_handler(flag.type))(flag.type, &ap, &flag);
			else if (flag.type != '\0')
				flag.len += ft_printf_sign(flag.type, &ap, &flag);
		}
		else
			ft_printf_vtouffet(&format, &flag);
	write(1, flag.buffer, flag.i);
	va_end(ap);
	return (flag.len);
}
