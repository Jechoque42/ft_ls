/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_color.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jechoque <jbchoquet@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/30 18:48:45 by jechoque          #+#    #+#             */
/*   Updated: 2017/11/30 20:24:36 by jechoque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

ssize_t		ft_get_color(const char *str, t_flag *fg)
{
	int len;
	int gtc;

	len = 0;
	gtc = 0;
	if (!ft_strncmp(str, "{red}", (len = 5)) && ++gtc)
		ft_buffnstr(RED, 5, fg);
	else if (!ft_strncmp(str, "{green}", (len = 7)) && ++gtc)
		ft_buffnstr(GREEN, 5, fg);
	else if (!ft_strncmp(str, "{yellow}", (len = 8)) && ++gtc)
		ft_buffnstr(YELLOW, 5, fg);
	else if (!ft_strncmp(str, "{blue}", (len = 6)) && ++gtc)
		ft_buffnstr(BLUE, 5, fg);
	else if (!ft_strncmp(str, "{purple}", (len = 8)) && ++gtc)
		ft_buffnstr(PURPLE, 5, fg);
	else if (!ft_strncmp(str, "{cyan}", (len = 6)) && ++gtc)
		ft_buffnstr(CYAN, 5, fg);
	else if (!ft_strncmp(str, "{eoc}", (len = 5)) && ++gtc)
		ft_buffnstr(EOC, 4, fg);
	if (gtc == 0)
		len = 0;
	return (len);
}
