/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_buff_utility.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jechoque <jbchoquet@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/24 13:30:40 by jechoque          #+#    #+#             */
/*   Updated: 2017/12/01 17:34:55 by jechoque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void		ft_buffwchar(wchar_t c, t_flag *fg)
{
	if (c <= 0x7F && ft_check_buffer(fg))
		fg->buffer[fg->i++] = c;
	else if (c <= 0x7FF && ft_check_buffer(fg))
	{
		fg->buffer[fg->i++] = ((c >> 6) + 0xC0);
		fg->buffer[fg->i++] = ((c & 0x3F) + 0x80);
	}
	else if (c <= 0xFFFF && ft_check_buffer(fg))
	{
		fg->buffer[fg->i++] = ((c >> 12) + 0xE0);
		fg->buffer[fg->i++] = (((c >> 6) & 0x3F) + 0x80);
		fg->buffer[fg->i++] = ((c & 0x3F) + 0x80);
	}
	else if (c <= 0x10FFFF && ft_check_buffer(fg))
	{
		fg->buffer[fg->i++] = ((c >> 18) + 0xF0);
		fg->buffer[fg->i++] = (((c >> 12) & 0x3F) + 0x80);
		fg->buffer[fg->i++] = (((c >> 6) & 0x3F) + 0x80);
		fg->buffer[fg->i++] = ((c & 0x3F) + 0x80);
	}
	ft_check_buffer(fg);
}

void		ft_buffnwstr(const wchar_t *str, size_t len, t_flag *fg)
{
	size_t	i;

	i = 0;
	while (*str && i < len)
	{
		if (*str <= 0x7F)
			i++;
		else if (*str <= 0x7FF)
			i += 2;
		else if (*str <= 0xFFFF)
			i += 3;
		else if (*str <= 0x10FFFF)
			i += 4;
		if (i <= len)
			ft_buffwchar(*str++, fg);
	}
}

void		ft_buffnstr(const char *str, int len, t_flag *fg)
{
	while (len--)
	{
		ft_check_buffer(fg);
		fg->buffer[fg->i++] = *str++;
	}
}

void		ft_buffpad(int width, ssize_t len, char pad, t_flag *fg)
{
	while (len++ < width)
	{
		ft_check_buffer(fg);
		fg->buffer[fg->i++] = pad;
	}
}

void		ft_buffbase(const char c, uintmax_t n, unsigned int base,
			t_flag *fg)
{
	char	*ref_base;

	if (c == 'b')
		ref_base = "01";
	else if (c == 'X')
		ref_base = "0123456789ABCDEF";
	else if (c == 'o')
		ref_base = "01234567";
	else if (c == 'x' || c == 'p')
		ref_base = "0123456789abcdef";
	else
		ref_base = "0123456789";
	if (n >= base)
	{
		ft_buffbase(c, n / base, base, fg);
		ft_buffbase(c, n % base, base, fg);
	}
	else
	{
		ft_check_buffer(fg);
		fg->buffer[fg->i++] = ref_base[n % base];
	}
}
