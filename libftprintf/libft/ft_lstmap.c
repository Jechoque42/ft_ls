/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jechoque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/06 17:34:37 by jechoque          #+#    #+#             */
/*   Updated: 2017/11/06 17:34:40 by jechoque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*map;

	map = NULL;
	if (lst && f)
	{
		map = (*f)(lst);
		lst = lst->next;
		while (lst)
		{
			ft_lstadd_back(&map, (*f)(lst));
			lst = lst->next;
		}
	}
	return (map);
}
