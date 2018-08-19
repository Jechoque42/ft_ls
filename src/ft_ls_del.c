/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_del.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jechoque <jbchoquet@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/06 20:18:39 by jechoque          #+#    #+#             */
/*   Updated: 2017/12/19 01:25:56 by jechoque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_ls.h"
#include <stdlib.h>

void	ft_ls_del_files(t_lstree **todel)
{
	if (*todel)
	{
		if ((*todel)->files)
			ft_ls_del_files(&(*todel)->files);
		if ((*todel)->path)
			free((*todel)->path);
		if ((*todel)->name)
			free((*todel)->name);
		if ((*todel)->access)
			free((*todel)->access);
		if ((*todel)->userg)
			free((*todel)->userg);
		if ((*todel)->usern)
			free((*todel)->usern);
		if ((*todel)->time)
			free((*todel)->time);
		(*todel)->files = NULL;
		(*todel)->directories = NULL;
		free(*todel);
		(*todel) = NULL;
	}
}
