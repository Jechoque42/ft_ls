/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jechoque <jbchoquet@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/07 17:40:06 by jechoque          #+#    #+#             */
/*   Updated: 2017/12/19 15:54:48 by jechoque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_ls.h"
#include <stdlib.h>
#include <dirent.h>
#include <errno.h>

static char		*ft_ls_joinpath(char *argv, char *cur_name)
{
	char		*new_path;
	int			len;
	int			i;

	i = 0;
	len = ft_strlen(argv) + ft_strlen(cur_name);
	new_path = (char*)malloc(sizeof(char) * len + 2);
	while (*argv)
		new_path[i++] = *argv++;
	new_path[i++] = '/';
	while (*cur_name)
		new_path[i++] = *cur_name++;
	new_path[i] = '\0';
	return (new_path);
}

static void		ft_ls_init(t_option *op)
{
	op->blocks = 0;
	op->padg.p_lnk = 0;
	op->padg.p_sze = 0;
	op->padg.p_usn = 0;
	op->padg.p_usg = 0;
}

static void		ft_ls_ford(struct dirent *cur_files, t_lstree **tree,
		t_option *op)
{
	t_lstree	*tmp;
	char		*cur_path;

	cur_path = NULL;
	if (ft_strncmp(".", cur_files->d_name, 1) ||
	(op->a || (op->upa && (ft_strncmp(".", cur_files->d_name, 2) &&
	ft_strncmp("..", cur_files->d_name, 3)))))
	{
		cur_path = ft_ls_joinpath((*tree)->path, cur_files->d_name);
		tmp = ft_ls_treenew(cur_path, op, cur_files->d_name);
		ft_strdel(&cur_path);
		if (op->upr && S_ISDIR(tmp->stats.st_mode) &&
		ft_strncmp(".", cur_files->d_name, 2) &&
		ft_strncmp("..", cur_files->d_name, 3))
			ft_ls_sort_tree(*tree, ft_ls_treenew(tmp->path, op, tmp->name),
					op, 'd');
		ft_ls_sort_tree(*tree, tmp, op, 'f');
		op->blocks += tmp->stats.st_blocks;
		ft_ls_padding(tmp, op);
	}
}

static void		ft_ls_parse_directory(t_option *op, t_lstree **tree)
{
	t_lstree		*tmp;
	DIR				*cur_dir;
	struct dirent	*cur_files;

	cur_dir = opendir((*tree)->path);
	ft_ls_init(op);
	while (cur_dir && (cur_files = readdir(cur_dir)))
		ft_ls_ford(cur_files, tree, op);
	if (!cur_dir && ((*tree)->error = errno))
		ft_ls_error(*tree);
	cur_dir ? closedir(cur_dir) : 0;
	ft_ls_display_lstree(*tree, op, 1);
	tmp = *tree;
	*tree = (*tree)->directories;
	ft_ls_del_files(&tmp);
}

void			ft_ls_parse_argv(char **argv, t_option *op, t_lstree **tree)
{
	t_lstree	*tmp;

	while ((tmp = ft_ls_treenew(*argv, op, NULL)))
	{
		if (!**argv++)
			ft_ls_error_fds(tree);
		if (!op->d && (S_ISDIR(tmp->stats.st_mode) ||
		(S_ISLNK(tmp->stats.st_mode) &&
		opendir(tmp->lpath))) && ++op->nbr_d)
			ft_ls_sort_tree(*tree, tmp, op, 'd');
		else
			ft_ls_sort_tree(*tree, tmp, op, 'f');
		if (!tmp->error)
			ft_ls_padding(tmp, op);
	}
	if ((*tree)->files)
		ft_ls_display_lstree((*tree)->files, op, ARGV);
	tmp = *tree;
	*tree = (*tree)->directories;
	ft_ls_del_files(&tmp);
	while (*tree)
		ft_ls_parse_directory(op, tree);
}
