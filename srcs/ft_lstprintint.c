/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstprintint.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sreijola <sreijola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/06 12:28:54 by sreijola          #+#    #+#             */
/*   Updated: 2021/02/18 15:36:43 by sreijola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

void	ft_lstprintint(t_list *lst)
{
	t_list	*temp;

	while (temp != NULL)
	{
		ft_printf("%d ->", *(int *)temp->content);
		temp = temp->next;
	}
	ft_printf("NULL\n");
}
