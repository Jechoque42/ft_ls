/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_tree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jechoque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/19 15:53:27 by jechoque          #+#    #+#             */
/*   Updated: 2017/12/19 16:01:04 by jechoque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include "../include/ft_ls.h"

static void			ft_ls_get_infos(t_lstree *tree, t_option *op)
{
	if (ft_strcmp(tree->path, "\0") != 0 && op->l)
		ft_ls_get_linfos(tree, op);
	if (S_ISLNK(tree->stats.st_mode))
		tree->lpath[readlink(tree->path, tree->lpath, L_BUFF)] = '\0';
	if (op->ups)
		tree->sort = tree->stats.st_size;
	else if (op->c)
		tree->sort = tree->stats.st_ctime;
	else if (op->u)
		tree->sort = tree->stats.st_atime;
	else
		tree->sort = tree->stats.st_mtime;
}

t_lstree			*ft_ls_treenew(char *path, t_option *op, char *name)
{
	t_lstree		*cur_tree;
	struct stat		*cur_stat;

	if (!path || !(cur_tree = malloc(sizeof(t_lstree))))
		return (NULL);
	cur_stat = &cur_tree->stats;
	ft_bzero(cur_tree, sizeof(t_lstree));
	cur_tree->name = (name ? ft_strdup(name) : ft_strdup(path));
	cur_tree->path = ft_strdup(path);
	if (lstat(path, cur_stat) != -1)
		ft_ls_get_infos(cur_tree, op);
	else
		cur_tree->error = errno;
	return (cur_tree);
}
