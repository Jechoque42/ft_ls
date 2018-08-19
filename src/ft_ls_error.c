/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jechoque <jbchoquet@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/07 05:48:58 by jechoque          #+#    #+#             */
/*   Updated: 2017/12/19 01:26:12 by jechoque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>
#include "../include/ft_ls.h"

void		ft_ls_error_fds(t_lstree **tree)
{
	ft_putstr_fd("ls: fts_open: No such file or directory\n", 2);
	ft_ls_del_files(tree);
	exit(1);
}

void		ft_ls_error_option(char c)
{
	char	*usage;

	usage = "usage: ls [-ARSTacdlprtu] [file ...]\n";
	ft_putstr_fd("/bin/ls: illegal option -- ", 2);
	ft_putchar_fd(c, 2);
	ft_putchar_fd('\n', 2);
	ft_putstr_fd(usage, 2);
	exit(1);
}

void		ft_ls_error_malloc(t_lstree **t_error)
{
	ft_putstr_fd("malloc error\n", 2);
	ft_ls_del_files(t_error);
	exit(1);
}

void		ft_ls_error(t_lstree *t_error)
{
	ft_putstr_fd("ls: ", 2);
	ft_putstr_fd(t_error->name, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(strerror(t_error->error), 2);
	ft_putchar_fd('\n', 2);
}
