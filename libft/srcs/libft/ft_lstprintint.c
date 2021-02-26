/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstprintint.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkarkaus <mkarkaus@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/06 12:28:54 by sreijola          #+#    #+#             */
/*   Updated: 2021/02/26 13:49:58 by mkarkaus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

void	ft_lstprintint(t_list *lst)
{
	t_list	*temp;

	temp = lst;
	while (temp != NULL)
	{
		ft_printf("%d ->", *(int *)temp->content);
		temp = temp->next;
	}
	ft_printf("NULL\n");
}
