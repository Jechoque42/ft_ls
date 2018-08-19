/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nbrlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jechoque <jbchoquet@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/25 10:39:08 by jechoque          #+#    #+#             */
/*   Updated: 2017/12/01 18:14:08 by jechoque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <inttypes.h>

int		ft_nbrlen(uintmax_t nbr, unsigned int base)
{
	int	len;

	len = 0;
	while (nbr)
	{
		nbr = nbr / base;
		len++;
	}
	return (len);
}
