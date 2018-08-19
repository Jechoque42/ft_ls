/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_conv_di.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jechoque <jbchoquet@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/30 13:56:45 by jechoque          #+#    #+#             */
/*   Updated: 2017/12/01 17:40:18 by jechoque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static intmax_t		ft_length_cast(va_list *arr, t_flag *fg)
{
	intmax_t	nbr;

	nbr = va_arg(*arr, intmax_t);
	if (fg->lgth == HH)
		nbr = (char)nbr;
	else if (fg->lgth == 'h')
		nbr = (short int)nbr;
	else if (fg->lgth == LL)
		nbr = (long long int)nbr;
	else if (fg->lgth == 'l')
		nbr = (long int)nbr;
	else if (fg->lgth == 'z')
		nbr = (size_t)nbr;
	else if (fg->lgth == 'j')
		nbr = (intmax_t)nbr;
	else
		nbr = (int)nbr;
	return (nbr);
}

ssize_t				ft_printf_int(const char c, va_list *arr, t_flag *fg)
{
	intmax_t	nbr;

	nbr = ft_length_cast(arr, fg);
	return (ft_printf_sgeneric(c, nbr, fg));
}
