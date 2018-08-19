/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jechoque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/21 13:14:43 by jechoque          #+#    #+#             */
/*   Updated: 2017/11/21 13:16:00 by jechoque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			ft_getnbr(const char *str)
{
	int		sign;
	int		rsl;

	sign = 1;
	rsl = 0;
	if (*str == '-' || *str == '+')
		if (*str++ == '-')
			sign = -1;
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (rsl);
		rsl = (rsl * 10) + (*str++ - '0');
	}
	rsl *= sign;
	return (rsl);
}
