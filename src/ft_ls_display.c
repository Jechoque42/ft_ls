/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_display.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jechoque <jbchoquet@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/06 20:08:48 by jechoque          #+#    #+#             */
/*   Updated: 2017/12/19 15:10:01 by jechoque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_ls.h"

static void		ft_ls_print_total(t_lstree **tree, t_option *op)
{
	if (op->first)
		ft_printf("%c", op->first);
	if (op->nbr_d > 2)
		op->l && (*tree)->files ?
		ft_printf("%s:\ntotal %zu\n", (*tree)->path, op->blocks) :
		ft_printf("%s:\n", (*tree)->path);
	else if (op->l && (*tree)->files)
		ft_printf("total %zu\n", op->blocks);
	*tree = (*tree)->files;
	(op->first = '\n');
}

static void		ft_ls_print_infos(t_lstree *tr, t_option *op)
{
	if (op->l)
		if (tr->access[0] == 'l')
			ft_printf("%s%c %*hu %-*s  %-*s  %*llu %s %s -> %s\n", tr->access,
			tr->acl, op->padg.p_lnk, tr->stats.st_nlink, (int)op->padg.p_usn,
			tr->usern, (int)op->padg.p_usg, tr->userg, op->padg.p_sze,
			tr->stats.st_size, tr->time, tr->name, tr->lpath);
		else if (S_ISCHR(tr->stats.st_mode) || S_ISBLK(tr->stats.st_mode))
			ft_printf("%s%c %*hu %-*s  %-*s  %d, %d %s %s\n", tr->access,
			tr->acl, op->padg.p_lnk, tr->stats.st_nlink, (int)op->padg.p_usn,
			tr->usern, (int)op->padg.p_usg, tr->userg, major(tr->stats.st_rdev),
			minor(tr->stats.st_rdev), tr->time, tr->name);
		else if (op->p && S_ISDIR(tr->stats.st_mode))
			ft_printf("%s%c %*hu %-*s  %-*s  %*llu %s %s/\n", tr->access,
			tr->acl, op->padg.p_lnk, tr->stats.st_nlink, (int)op->padg.p_usn,
			tr->usern, (int)op->padg.p_usg, tr->userg, op->padg.p_sze,
			tr->stats.st_size, tr->time, tr->name);
		else
			ft_printf("%s%c %*hu %-*s  %-*s  %*llu %s %s\n", tr->access,
			tr->acl, op->padg.p_lnk, tr->stats.st_nlink, (int)op->padg.p_usn,
			tr->usern, (int)op->padg.p_usg, tr->userg, op->padg.p_sze,
			tr->stats.st_size, tr->time, tr->name);
	else
		(op->p && S_ISDIR(tr->stats.st_mode)) ?
		ft_printf("%s/\n", tr->name) : ft_printf("%s\n", tr->name);
	(op->first = '\n');
}

void			ft_ls_display_lstree(t_lstree *tree, t_option *op, int mod)
{
	int	len;

	len = 0;
	if (mod != ARGV && ++op->nbr_d)
		ft_ls_print_total(&tree, op);
	while (tree)
	{
		if (tree->error && ++op->nbr_d)
			ft_ls_error(tree);
		if (!tree->error && (ft_strncmp(".", tree->name, 1) ||
		(op->a || op->upa) || !mod))
			ft_ls_print_infos(tree, op);
		tree = tree->files;
	}
}
