/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstprint.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkarkaus <mkarkaus@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/24 12:36:19 by mkarkaus          #+#    #+#             */
/*   Updated: 2020/09/24 12:39:50 by mkarkaus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

void	ft_lstprint(t_list *alst)
{
	while (alst != NULL)
	{
		ft_printf("%s\n", alst->content);
		alst = alst->next;
	}
}
