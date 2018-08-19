/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utility.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jechoque <jbchoquet@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/30 15:22:16 by jechoque          #+#    #+#             */
/*   Updated: 2017/12/01 17:39:06 by jechoque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "ft_printf.h"

int		ft_check_buffer(t_flag *fg)
{
	if (fg->i >= BUFF_SIZE_PF)
	{
		write(1, fg->buffer, fg->i);
		fg->i = 0;
	}
	return (1);
}

int		ft_isflag(int c)
{
	if (c == '#' || c == '+' || c == '-' || c == ' ' || c == '0')
		return (1);
	return (0);
}

int		ft_islength(int c)
{
	if (c == 'h' || c == 'l' || c == 'j' || c == 'z')
		return (1);
	return (0);
}

int		ft_istype(int c)
{
	if (c == 's' || c == 'S' || c == 'c' || c == 'C' || c == '%' ||
		c == 'd' || c == 'i' || c == 'D' || c == 'O' || c == 'U' || c == 'p' ||
		c == 'o' || c == 'u' || c == 'x' || c == 'X' || c == 'b' || c == 'f' ||
		c == 'F' || c == 'n')
		return (1);
	return (0);
}
