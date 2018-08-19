/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jechoque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/08 15:17:21 by jechoque          #+#    #+#             */
/*   Updated: 2017/11/21 17:58:09 by jechoque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include "libft.h"

static void			ft_strsubdel(t_list *cr, int start, int end)
{
	char			*tmp;

	tmp = cr->content;
	cr->content = ft_strsub(cr->content, start, end);
	free(tmp);
	tmp = NULL;
}

static void			ft_strjoindel(t_list *cr, char *s2)
{
	char			*tmp;

	tmp = cr->content;
	cr->content = ft_strjoin(cr->content, s2);
	free(tmp);
	tmp = NULL;
}

static int			ft_strcpy_c(char **dst, char *src, char c)
{
	int				len;
	int				stock;
	char			*cpy;

	len = 0;
	stock = 0;
	while (src[len] && src[len] != c)
		len++;
	cpy = ft_strnew(len + 1);
	while ((len > stock))
	{
		cpy[stock] = *src++;
		stock++;
	}
	*dst = cpy;
	return (stock);
}

static t_list		*ft_check_fd(const int fd, t_list **check)
{
	t_list			*tmp;

	tmp = *check;
	while (tmp)
	{
		if (tmp->content_size == (size_t)fd)
			return (tmp);
		tmp = tmp->next;
	}
	tmp = ft_lstnew("\0", fd);
	ft_lstadd(check, tmp);
	tmp = *check;
	return (tmp);
}

int					get_next_line(const int fd, char **line)
{
	char			buf[BUFF_SIZE + 1];
	static t_list	*fds;
	t_list			*cr;
	size_t			len;

	if (fd == -1 || !line || read(fd, buf, 0) == -1 || BUFF_SIZE < 1)
		return (-1);
	cr = ft_check_fd(fd, &fds);
	while (!ft_strchr(cr->content, '\n') && (len = read(fd, buf, BUFF_SIZE)))
	{
		buf[len] = '\0';
		ft_strjoindel(cr, buf);
	}
	if (len < BUFF_SIZE && !ft_strlen(cr->content))
	{
		cr = NULL;
		return (0);
	}
	len = ft_strcpy_c(line, cr->content, '\n');
	(len + 1 < ft_strlen(cr->content) ?
	ft_strsubdel(cr, len + 1, ft_strlen(cr->content) - len)
	: ft_strclr(cr->content));
	cr = NULL;
	return (1);
}
