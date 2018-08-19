/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_sort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jechoque <jbchoquet@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/06 20:07:28 by jechoque          #+#    #+#             */
/*   Updated: 2017/12/19 15:32:04 by jechoque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_ls.h"

static void	ft_ls_sort_ascii(t_lstree *tree, t_lstree *new, char c)
{
	if (c == 'f')
	{
		if (!(tree)->files)
			(tree)->files = new;
		else if (ft_strcmp(new->name, (tree)->files->name) <= 0 &&
				(new->files = tree->files))
			tree->files = new;
		else
			ft_ls_sort_ascii((tree)->files, new, 'f');
	}
	else if (c == 'd')
	{
		if (!((tree)->directories))
			(tree)->directories = new;
		else if (ft_strcmp(new->path, tree->directories->path) <= 0 &&
				(new->directories = (tree)->directories))
			tree->directories = new;
		else
			ft_ls_sort_ascii((tree)->directories, new, 'd');
	}
}

static void	ft_ls_sort_rascii(t_lstree *tree, t_lstree *new, char c)
{
	if (c == 'f')
	{
		if (!(tree)->files)
			(tree)->files = new;
		else if (ft_strcmp(new->name, (tree)->files->name) >= 0 &&
				(new->files = (tree)->files))
			tree->files = new;
		else
			ft_ls_sort_rascii((tree)->files, new, 'f');
	}
	else if (c == 'd')
	{
		if (!((tree)->directories))
			(tree)->directories = new;
		else if (ft_strcmp(new->path, tree->directories->path) >= 0)
			(new->directories = (tree)->directories) &&
			((tree)->directories = new);
		else
			ft_ls_sort_rascii((tree)->directories, new, 'd');
	}
}

static void	ft_ls_sort_time(t_lstree *tree, t_lstree *new, char c)
{
	if (c == 'f')
	{
		if (!(tree)->files)
			(tree)->files = new;
		else if ((new->sort > tree->files->sort ||
				(new->sort == tree->files->sort
				&& ft_strcmp(new->name, (tree)->files->name) <= 0))
				&& (new->files = (tree)->files))
			tree->files = new;
		else
			ft_ls_sort_time((tree)->files, new, 'f');
	}
	else if (c == 'd')
	{
		if (!((tree)->directories))
			(tree)->directories = new;
		else if (new->sort > tree->directories->sort ||
			(new->sort == tree->directories->sort &&
			ft_strcmp(new->path, (tree)->directories->path) <= 0))
			(new->directories = (tree)->directories) &&
			((tree)->directories = new);
		else
			ft_ls_sort_time((tree)->directories, new, 'd');
	}
}

static void	ft_ls_sort_rtime(t_lstree *tree, t_lstree *new, char c)
{
	if (c == 'f')
	{
		if (!(tree)->files)
			(tree)->files = new;
		else if ((new->sort < tree->files->sort ||
			(new->sort == tree->files->sort &&
			ft_strcmp(new->name, (tree)->files->name) >= 0)) &&
			(new->files = (tree)->files))
			tree->files = new;
		else
			ft_ls_sort_rtime((tree)->files, new, 'f');
	}
	else if (c == 'd')
	{
		if (!((tree)->directories))
			(tree)->directories = new;
		else if (new->sort < tree->directories->sort ||
			(new->sort == tree->directories->sort &&
			ft_strcmp(new->path, (tree)->directories->path) >= 0))
			(new->directories = (tree)->directories) &&
			((tree)->directories = new);
		else
			ft_ls_sort_rtime((tree)->directories, new, 'd');
	}
}

void		ft_ls_sort_tree(t_lstree *tree, t_lstree *new, t_option *op,
		char c)
{
	if ((op->r && (op->t || op->ups)))
		ft_ls_sort_rtime(tree, new, c);
	else if (op->r)
		ft_ls_sort_rascii(tree, new, c);
	else if (op->t || op->ups)
		ft_ls_sort_time(tree, new, c);
	else
		ft_ls_sort_ascii(tree, new, c);
}
