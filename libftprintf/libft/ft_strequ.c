/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strequ.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jechoque <jbchoquet@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/05 22:28:23 by jechoque          #+#    #+#             */
/*   Updated: 2017/11/08 02:23:03 by jechoque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		ft_strequ(char const *s1, char const *s2)
{
	if (s1 && s2)
		while (*s1 || *s2)
			if (*s1++ != *s2++)
				return (0);
	return (1);
}
