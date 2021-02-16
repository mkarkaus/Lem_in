/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstfree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sreijola <sreijola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/07 11:12:51 by sreijola          #+#    #+#             */
/*   Updated: 2021/02/16 17:32:56 by sreijola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

void	ft_lstfree(t_list *lst)
{
	t_list	*tmp;
	int		i;

	i = -1;
	while (lst)
	{
		// ft_printf("i:%d, content:%s\n", ++i, lst->content);
		tmp = lst;
		lst = lst->next;
		free(tmp->content);
		free(tmp);
	}
}
