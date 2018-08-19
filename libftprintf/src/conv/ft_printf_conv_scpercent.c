/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_conv_scpercent.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jechoque <jbchoquet@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/30 13:43:49 by jechoque          #+#    #+#             */
/*   Updated: 2017/12/01 18:08:11 by jechoque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

ssize_t		ft_printf_str(const char c, va_list *arr, t_flag *fg)
{
	const char	*str;
	ssize_t		len;

	(void)c;
	if (fg->lgth == 'l')
		return (ft_get_handler('S')('S', arr, fg));
	str = va_arg(*arr, const char*);
	str = (!str) ? "(null)" : str;
	len = ft_strlen(str);
	if (fg->prec >= 0)
		len = len > fg->prec ? fg->prec : len;
	if (fg->wdth && !fg->minu)
		ft_buffpad(fg->wdth, len, fg->zero ? '0' : ' ', fg);
	if (c == 'S' && ft_strcmp(str, "(null)"))
	{
		len = ft_wstrlen((wchar_t*)str);
		ft_buffnwstr((wchar_t*)str, len, fg);
	}
	else
		ft_buffnstr(str, len, fg);
	if (fg->wdth && fg->minu)
		ft_buffpad(fg->wdth, len, ' ', fg);
	return (len < fg->wdth ? fg->wdth : len);
}

ssize_t		ft_printf_wstr(const char c, va_list *arr, t_flag *fg)
{
	wchar_t		*str;
	int			i;
	ssize_t		len;
	ssize_t		charlen;

	(void)c;
	i = 0;
	len = 0;
	charlen = 0;
	if (fg->lgth == HH)
		return (ft_get_handler('s')('S', arr, fg));
	str = va_arg(*arr, wchar_t*);
	if (str == NULL)
		str = L"(null)";
	if (fg->prec > 0 && len + charlen < fg->prec)
		while (len + charlen <= fg->prec && (charlen = ft_wcharlen(str[i++])))
			len += charlen;
	else if (fg->prec < 0)
		len = ft_wstrlen(str);
	if (fg->wdth && !fg->minu)
		ft_buffpad(fg->wdth, len, fg->zero ? '0' : ' ', fg);
	ft_buffnwstr(str, len, fg);
	if (fg->wdth && fg->minu)
		ft_buffpad(fg->wdth, len, ' ', fg);
	return (fg->wdth > len ? fg->wdth : len);
}

ssize_t		ft_printf_char(const char format, va_list *arr, t_flag *fg)
{
	ssize_t		len;
	int			c;

	(void)format;
	if (fg->lgth == 'l')
		return (ft_get_handler('C')('C', arr, fg));
	c = va_arg(*arr, int);
	len = 1;
	if (format == 'C')
		len = ft_wcharlen(c);
	if (fg->wdth && !fg->minu)
		ft_buffpad(fg->wdth, len, fg->zero ? '0' : ' ', fg);
	ft_check_buffer(fg);
	fg->buffer[fg->i++] = c;
	if (fg->wdth && fg->minu)
		ft_buffpad(fg->wdth, len, ' ', fg);
	return (len < fg->wdth ? fg->wdth : len);
}

ssize_t		ft_printf_wchar(const char format, va_list *arr, t_flag *fg)
{
	ssize_t		len;
	wchar_t		c;

	(void)format;
	if (fg->lgth == HH)
		return (ft_get_handler('c')('C', arr, fg));
	c = va_arg(*arr, wchar_t);
	len = ft_wcharlen(c);
	if (fg->wdth && !fg->minu)
		ft_buffpad(fg->wdth, len, fg->zero ? '0' : ' ', fg);
	ft_buffwchar(c, fg);
	if (fg->wdth && fg->minu)
		ft_buffpad(fg->wdth, len, ' ', fg);
	return (len < fg->wdth ? fg->wdth : len);
}

ssize_t		ft_printf_sign(const char c, va_list *arr, t_flag *fg)
{
	ssize_t		len;

	(void)*arr;
	len = 1;
	if (fg->wdth && !fg->minu)
		ft_buffpad(fg->wdth, len, fg->zero ? '0' : ' ', fg);
	ft_check_buffer(fg);
	fg->buffer[fg->i++] = c;
	if (fg->wdth && fg->minu)
		ft_buffpad(fg->wdth, len, ' ', fg);
	return (len < fg->wdth ? fg->wdth : len);
}
