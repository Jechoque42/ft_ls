/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_conv_generic.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jechoque <jbchoquet@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/30 14:24:50 by jechoque          #+#    #+#             */
/*   Updated: 2017/12/01 18:10:50 by jechoque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

uintmax_t	ft_length_ucast(va_list *arr, t_flag *fg)
{
	uintmax_t	nbr;

	nbr = va_arg(*arr, uintmax_t);
	if (fg->lgth == HH)
		nbr = (unsigned char)nbr;
	else if (fg->lgth == 'h')
		nbr = (unsigned short int)nbr;
	else if (fg->lgth == LL)
		nbr = (unsigned long long int)nbr;
	else if (fg->lgth == 'l')
		nbr = (unsigned long int)nbr;
	else if (fg->lgth == 'z')
		nbr = (size_t)nbr;
	else if (fg->lgth == 'j')
		nbr = (uintmax_t)nbr;
	else
		nbr = (unsigned int)nbr;
	return (nbr);
}

ssize_t		ft_printf_ugeneric(const char c, uintmax_t nbr, t_flag *fg,
			int base)
{
	ssize_t	len;
	ssize_t print;

	len = ((!nbr && !fg->prec) || nbr ? ft_nbrlen(nbr, base) : 1);
	print = (fg->dies && (nbr || c == 'o' || c == 'p') ?
	ft_strlen(fg->pref) : 0);
	print += fg->prec > len ? fg->prec : len;
	if (fg->wdth && !fg->minu && !fg->zero)
		ft_buffpad(fg->wdth, print, ' ', fg);
	if (fg->dies && (nbr || c == 'o' || c == 'p'))
		while (*fg->pref && ft_check_buffer(fg))
			fg->buffer[fg->i++] = *fg->pref++;
	if (fg->wdth && fg->zero)
		ft_buffpad(fg->wdth, print, '0', fg);
	if (fg->prec > len)
		ft_buffpad(fg->prec, len, '0', fg);
	(!nbr && (!fg->prec || (c == 'o' && fg->dies))) ?
		0 : ft_buffbase(c, nbr, base, fg);
	if (fg->wdth && fg->minu)
		ft_buffpad(fg->wdth, print, ' ', fg);
	return (fg->wdth > print ? fg->wdth : print);
}

ssize_t		ft_printf_sgeneric(const char c, intmax_t nbr, t_flag *fg)
{
	ssize_t		len;
	ssize_t		print;

	if (fg->spac && fg->zero && fg->prec < 0)
	{
		fg->prec = fg->wdth - 1;
		fg->zero = 0;
	}
	len = ((!nbr && !fg->prec) || nbr ? ft_nbrlen(ABS(nbr), 10) : 1);
	print = fg->prec > len ? fg->prec : len;
	print += ((fg->plus && nbr >= 0) || nbr < 0 ? 1 : 0);
	fg->wdth = fg->wdth < len && fg->spac ? len + 1 : fg->wdth;
	if (fg->wdth && !fg->minu && (!fg->zero || fg->spac))
		ft_buffpad(fg->wdth, print, ' ', fg);
	fg->plus && nbr >= 0 && ft_check_buffer(fg) ? fg->buffer[fg->i++] = '+' : 0;
	if ((nbr < 0 || (nbr <= 0 && c == 'f')) && ft_check_buffer(fg))
		fg->buffer[fg->i++] = '-';
	if (fg->prec > len)
		ft_buffpad(fg->prec, len, '0', fg);
	if (fg->wdth && fg->zero && !fg->spac)
		ft_buffpad(fg->wdth, print, '0', fg);
	!fg->prec && !nbr ? 0 : ft_buffbase(c, ABS(nbr), 10, fg);
	if (fg->wdth && fg->minu)
		ft_buffpad(fg->wdth, print, ' ', fg);
	return (fg->wdth > print ? fg->wdth : print);
}
