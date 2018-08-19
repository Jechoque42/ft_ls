/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_conv_pouxb.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jechoque <jbchoquet@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/30 14:29:09 by jechoque          #+#    #+#             */
/*   Updated: 2017/12/01 17:43:14 by jechoque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

ssize_t		ft_printf_ptr(const char c, va_list *arr, t_flag *fg)
{
	uintmax_t	nbr;

	fg->pref = "0x";
	fg->dies = '#';
	fg->lgth = 'j';
	nbr = ft_length_ucast(arr, fg);
	return (ft_printf_ugeneric(c, nbr, fg, 16));
}

ssize_t		ft_printf_octal(const char c, va_list *arr, t_flag *fg)
{
	uintmax_t	nbr;

	fg->pref = "0";
	nbr = ft_length_ucast(arr, fg);
	if (!nbr)
		fg->dies = !fg->prec ? fg->dies : 0;
	else
		fg->dies = fg->prec <= ft_nbrlen(nbr, 8) ? fg->dies : 0;
	return (ft_printf_ugeneric(c, nbr, fg, 8));
}

ssize_t		ft_printf_uint(const char c, va_list *arr, t_flag *fg)
{
	uintmax_t	nbr;

	fg->pref = "\0";
	nbr = ft_length_ucast(arr, fg);
	return (ft_printf_ugeneric(c, nbr, fg, 10));
}

ssize_t		ft_printf_hexa(const char c, va_list *arr, t_flag *fg)
{
	uintmax_t	nbr;

	if (c == 'x' || c == 'p')
		fg->pref = "0x";
	if (c == 'X')
		fg->pref = "0X";
	nbr = ft_length_ucast(arr, fg);
	return (ft_printf_ugeneric(c, nbr, fg, 16));
}

ssize_t		ft_printf_binary(const char c, va_list *arr, t_flag *fg)
{
	uintmax_t	nbr;

	fg->lgth = 'j';
	nbr = ft_length_ucast(arr, fg);
	return (ft_printf_ugeneric(c, nbr, fg, 2));
}
