/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_options.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jechoque <jbchoquet@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/06 20:03:27 by jechoque          #+#    #+#             */
/*   Updated: 2017/12/19 14:40:25 by jechoque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "../include/ft_ls.h"

static void		ft_ls_upoption(int c, t_option *op)
{
	if (c == 'A')
		op->upa = 1;
	else if (c == 'R')
		op->upr = 1;
	else if (c == 'S')
		op->ups = 1;
	else if (c == 'T')
		op->upt = 1;
	else if (c == '1')
		op->one = 1;
}

static int		ft_ls_getoption(int c, t_option *op)
{
	if (c == 'a')
		op->a = 1;
	else if (c == 'c')
		op->c = 1;
	else if (c == 'd')
		op->d = 1;
	else if (c == 'l')
		op->l = 1;
	else if (c == 'p')
		op->p = 1;
	else if (c == 'r')
		op->r = 1;
	else if (c == 't')
		op->t = 1;
	else if (c == 'u')
		op->u = 1;
	else if (c == 'A' || c == 'R' || c == 'S' || c == 'T' || c == '1')
		ft_ls_upoption(c, op);
	else
		return (0);
	return (1);
}

int				ft_ls_parse_options(char **argv, t_option *op)
{
	char		**tmp;

	tmp = argv;
	op->one = '\t';
	while (*++argv && *argv[0] == '-')
	{
		if (ft_strncmp(*argv, "-", 2) == 0)
			return (argv - tmp);
		if (ft_strncmp(*argv, "--", 3) == 0)
			return (++argv - tmp);
		while (ft_ls_getoption(*(++*argv), op))
			;
		if (**argv)
			ft_ls_error_option(**argv);
	}
	return (argv - tmp);
}
