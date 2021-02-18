/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sreijola <sreijola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 13:02:41 by sreijola          #+#    #+#             */
/*   Updated: 2021/02/18 15:36:55 by sreijola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "./includes/libft.h"
#include "../includes/lem_in.h"

int		ft_lstlen(t_list *lst)
{
	int	i;

	i = 0;
	while (lst)
	{
		lst = lst->next;
		i++;
	}
	return (i);
}
