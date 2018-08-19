/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_conv_f.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jechoque <jbchoquet@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/30 14:45:37 by jechoque          #+#    #+#             */
/*   Updated: 2017/12/01 17:47:14 by jechoque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	ft_printf_modif_flags(int *decimale, t_flag *fg, int len, int n)
{
	(void)len;
	if (fg->prec < 0)
		fg->prec = 6;
	if (fg->prec > 0)
	{
		*decimale = 10;
		fg->wdth -= len + fg->prec;
		fg->wdth = fg->wdth < 0 ? 0 : fg->wdth;
	}
	while (--fg->prec > 0)
		*decimale *= 10;
	fg->prec = !n && fg->prec == 0 ? 1 : fg->prec;
}

ssize_t		ft_printf_float(const char c, va_list *arr, t_flag *fg)
{
	double		nbr;
	intmax_t	n;
	ssize_t		len;
	int			decimale;

	len = 1;
	decimale = 0;
	nbr = va_arg(*arr, double);
	n = nbr;
	len += !n && nbr < 0 ? 1 : 0;
	ft_printf_modif_flags(&decimale, fg, len, n);
	len += ft_printf_sgeneric(c, n, fg);
	if (decimale != 0 && ft_check_buffer(fg))
	{
		fg->buffer[fg->i++] = '.';
		fg->wdth = 0;
		n = (ABS(nbr - n)) * decimale + (ABS(n) == 1 ? 1 : 0);
		len += ft_printf_sgeneric(c, n, fg);
	}
	return (len);
}
