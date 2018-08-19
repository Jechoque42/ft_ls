/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_padding.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jechoque <jbchoquet@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/07 06:06:27 by jechoque          #+#    #+#             */
/*   Updated: 2017/12/19 01:26:27 by jechoque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_ls.h"

void		ft_ls_padding(t_lstree *tree, t_option *op)
{
	op->padg.p_sze = ft_nbrlen(tree->stats.st_size, 10) > op->padg.p_sze ?
	ft_nbrlen(tree->stats.st_size, 10) : op->padg.p_sze;
	op->padg.p_lnk = ft_nbrlen(tree->stats.st_nlink, 10) > op->padg.p_lnk ?
	ft_nbrlen(tree->stats.st_nlink, 10) : op->padg.p_lnk;
	if (op->l)
	{
		op->padg.p_usn = ft_strlen(tree->usern) > op->padg.p_usn ?
		ft_strlen(tree->usern) : op->padg.p_usn;
		op->padg.p_usg = ft_strlen(tree->userg) > op->padg.p_usg ?
		ft_strlen(tree->userg) : op->padg.p_usg;
	}
	op->padg.name = ft_strlen(tree->name) > op->padg.name ?
	ft_strlen(tree->name) : op->padg.name;
}
