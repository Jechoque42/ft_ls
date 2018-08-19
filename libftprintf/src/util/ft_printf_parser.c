/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_parser.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jechoque <jbchoquet@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/30 15:18:26 by jechoque          #+#    #+#             */
/*   Updated: 2017/12/01 17:36:38 by jechoque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static ssize_t		ft_parse_flag(const char *format, t_flag *fg)
{
	const char *tmp;

	tmp = format;
	while (ft_isflag(*format))
	{
		if (*format == '#')
			fg->dies = 1;
		else if (*format == '+')
			fg->plus = 1;
		else if (*format == '-')
			fg->minu = 1;
		else if (*format == '0')
			fg->zero = 1;
		else if (*format == ' ')
			fg->spac = 1;
		format++;
		if (fg->minu)
			fg->zero = 0;
	}
	return (format - tmp);
}

static ssize_t		ft_parse_width(const char *format, t_flag *fg, va_list *arr)
{
	const char *tmp;

	tmp = format;
	while (*format == '*' || ft_isdigit(*format))
	{
		if (*format == '*')
		{
			fg->wdth = va_arg(*arr, int);
			fg->minu = fg->wdth < 0 ? 1 : fg->minu;
			fg->wdth = fg->wdth < 0 ? ABS(fg->wdth) : fg->wdth;
			format++;
		}
		else if (ft_isdigit(*format))
		{
			fg->wdth = ft_getnbr(format);
			format += ft_nbrlen(fg->wdth, 10);
		}
	}
	return (format - tmp);
}

static ssize_t		ft_parse_precision(const char *format, t_flag *fg,
					va_list *arr)
{
	const char *tmp;

	tmp = format;
	if (*format == '.' && *format++)
	{
		fg->prec = 0;
		if (*format == '*' && format++)
		{
			fg->prec = va_arg(*arr, int);
			return (format - tmp);
		}
		else if (ft_isdigit(*format))
		{
			fg->prec = ft_getnbr(format);
			while (ft_isdigit(*format))
				format++;
		}
	}
	return (format - tmp);
}

static ssize_t		ft_parse_length(const char *format, t_flag *fg)
{
	const char *tmp;

	tmp = format;
	if (ft_islength(*format) && !fg->lgth)
	{
		fg->lgth = *format++;
		if ((*format == 'h' || *format == 'l') && !ft_islength(*(format + 1)))
			fg->lgth == *format && format++ ? fg->lgth++ : 0;
	}
	else if (ft_islength(*format) && fg->lgth)
		format++;
	return (format - tmp);
}

ssize_t				ft_getflag(t_flag *fg, const char *format, va_list *arr)
{
	const char *tmp;

	tmp = format;
	while (ft_isflag(*format) || ft_isdigit(*format) || ft_islength(*format) ||
	*format == '.' || *format == '*')
	{
		*format ? format += ft_parse_flag(format, fg) : 0;
		*format ? format += ft_parse_width(format, fg, arr) : 0;
		*format ? format += ft_parse_precision(format, fg, arr) : 0;
		*format ? format += ft_parse_length(format, fg) : 0;
	}
	if (*format == 'd')
		fg->zero = (fg->prec >= 0 && fg->prec < fg->wdth ? 0 : fg->zero);
	return (format - tmp);
}
