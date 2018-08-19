/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jechoque <jbchoquet@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/03 00:28:30 by jechoque          #+#    #+#             */
/*   Updated: 2017/12/19 01:26:55 by jechoque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_ls.h"

int			main(int argc, char **argv)
{
	t_option	options;
	t_lstree	*f_d_infos;

	if (!(f_d_infos = ft_ls_treenew("", &options, "root")))
		ft_ls_error_malloc(&f_d_infos);
	ft_bzero(&options, sizeof(options));
	if (argc >= 1)
		argv += ft_ls_parse_options(argv, &options);
	if (!*argv && options.d)
	{
		if (!(f_d_infos->files = ft_ls_treenew(".", &options, ".")))
			ft_ls_error_malloc(&f_d_infos);
	}
	else if (!*argv && ++options.nbr_d)
	{
		if (!(f_d_infos->directories = ft_ls_treenew(".", &options, "root")))
			ft_ls_error_malloc(&f_d_infos);
	}
	ft_ls_parse_argv(argv, &options, &f_d_infos);
	return (0);
}
