/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jechoque <jbchoquet@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/03 00:32:40 by jechoque          #+#    #+#             */
/*   Updated: 2017/12/19 15:55:53 by jechoque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include "../libftprintf/libft/libft.h"
# include "../libftprintf/include/ft_printf.h"
# include <stdlib.h>
# include <stdio.h>
# include <sys/xattr.h>
# include <sys/acl.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <unistd.h>

# define ARGV 0
# define L_BUFF 2048

typedef struct		s_pad
{
	int				p_lnk;
	int				p_sze;
	size_t			p_usn;
	size_t			p_usg;
	size_t			name;
}					t_pad;

typedef struct		s_option
{
	int				a;
	int				c;
	int				d;
	int				l;
	int				p;
	int				r;
	int				t;
	int				u;
	int				upa;
	int				upr;
	int				ups;
	int				upt;
	int				one;
	t_pad			padg;
	char			first;
	uintmax_t		blocks;
	int				nbr_d;
}					t_option;

typedef struct		s_lstree
{
	char			*path;
	char			lpath[L_BUFF];
	char			*name;
	char			*access;
	char			acl;
	char			*usern;
	char			*userg;
	struct stat		stats;
	char			*time;
	time_t			sort;
	int				error;
	struct s_lstree	*files;
	struct s_lstree	*directories;
}					t_lstree;

void				ft_ls_get_linfos(t_lstree *tree, t_option *op);
int					ft_ls_parse_options(char **argv, t_option *op);
void				ft_ls_display_lstree(t_lstree *tree, t_option *op, int a);
void				ft_ls_sort_tree(t_lstree *tree, t_lstree *new, t_option *op,
					char c);
t_lstree			*ft_ls_treenew(char *path, t_option *op, char *name);
void				ft_ls_del_files(t_lstree **todel);
void				ft_ls_error_option(char c);
void				ft_ls_error(t_lstree *t_error);
void				ft_ls_error_malloc(t_lstree **t_error);
void				ft_ls_padding(t_lstree *cur_tree, t_option *op);
void				ft_ls_error_fds(t_lstree **tree);
void				ft_ls_parse_argv(char **argv, t_option *op,
					t_lstree **tree);

#endif
