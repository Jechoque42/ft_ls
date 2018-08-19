/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_create.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jechoque <jbchoquet@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/06 20:14:21 by jechoque          #+#    #+#             */
/*   Updated: 2017/12/19 15:57:16 by jechoque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <grp.h>
#include <pwd.h>
#include <time.h>
#include "../include/ft_ls.h"

static char			ft_ls_gettype(mode_t st_mode)
{
	if (S_ISFIFO(st_mode))
		return ('p');
	else if (S_ISCHR(st_mode))
		return ('c');
	else if (S_ISDIR(st_mode))
		return ('d');
	else if (S_ISBLK(st_mode))
		return ('b');
	else if (S_ISREG(st_mode))
		return ('-');
	else if (S_ISLNK(st_mode))
		return ('l');
	else if (S_ISSOCK(st_mode))
		return ('s');
	else
		return (' ');
}

static char			*ft_ls_getaccess(mode_t st_mode)
{
	char			*access;

	access = ft_strnew(11);
	*access = ft_ls_gettype(st_mode);
	*++access = ((st_mode & S_IRUSR) ? 'r' : '-');
	*++access = ((st_mode & S_IWUSR) ? 'w' : '-');
	*++access = ((st_mode & S_IXUSR) ? 'x' : '-');
	if ((st_mode & S_ISUID))
		*access = (*access == 'x' ? 's' : 'S');
	*++access = ((st_mode & S_IRGRP) ? 'r' : '-');
	*++access = ((st_mode & S_IWGRP) ? 'w' : '-');
	*++access = ((st_mode & S_IXGRP) ? 'x' : '-');
	if ((st_mode & S_ISGID))
		*access = (*access == 'x' ? 's' : 'S');
	*++access = ((st_mode & S_IROTH) ? 'r' : '-');
	*++access = ((st_mode & S_IWOTH) ? 'w' : '-');
	*++access = ((st_mode & S_IXOTH) ? 'x' : '-');
	if ((st_mode & S_ISVTX))
		*access = (*access == 'x' ? 't' : 'T');
	*++access = '\0';
	return (access - 10);
}

static char			*ft_ls_get_time(t_option *op, time_t data)
{
	time_t			now;
	time_t			dif;
	char			*file_t;
	char			*rsl;
	int				i;

	now = time(NULL);
	dif = now - data;
	file_t = ctime(&data);
	if ((i = ft_strlen(file_t + 4)) && op->upt)
		return (ft_strncpy(ft_strnew(i), file_t + 4, i - 1));
	if (!(rsl = malloc(sizeof(char) * ft_strlen(file_t))))
		return (NULL);
	i = -1;
	while (++i != 6)
		rsl[i] = file_t[4 + i];
	rsl[i] = ' ';
	if ((dif < (-15811200) || dif > (15811200)) && (rsl[++i] = ' '))
		while (file_t[12 + ++i] != '\n')
			rsl[i] = file_t[12 + i];
	else
		while (++i != 12)
			rsl[i] = file_t[4 + i];
	rsl[i] = '\0';
	return (rsl);
}

static char			ft_ls_get_acl(char *path)
{
	acl_t			acl;

	if ((int)listxattr(path, NULL, 1, XATTR_NOFOLLOW) > 0)
		return ('@');
	else
	{
		acl = acl_get_file(path, ACL_TYPE_EXTENDED);
		if (acl != NULL)
		{
			free(acl);
			return ('+');
		}
		else
			return (' ');
	}
}

void				ft_ls_get_linfos(t_lstree *tree, t_option *op)
{
	struct passwd	*cur_pass;
	struct group	*cur_grp;

	cur_pass = getpwuid(tree->stats.st_uid);
	cur_grp = getgrgid(tree->stats.st_gid);
	tree->usern = cur_pass ? ft_strdup(cur_pass->pw_name)
	: ft_itoa(tree->stats.st_uid);
	tree->userg = cur_grp ? ft_strdup(cur_grp->gr_name)
	: ft_itoa(tree->stats.st_gid);
	tree->access = ft_ls_getaccess(tree->stats.st_mode);
	tree->acl = ft_ls_get_acl(tree->path);
	if (op->u)
		tree->time = ft_ls_get_time(op, tree->stats.st_atime);
	else if (op->c)
		tree->time = ft_ls_get_time(op, tree->stats.st_ctime);
	else
		tree->time = ft_ls_get_time(op, tree->stats.st_mtime);
}
