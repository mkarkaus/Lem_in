/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstapp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkarkaus <mkarkaus@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/24 10:25:30 by mkarkaus          #+#    #+#             */
/*   Updated: 2020/09/24 12:39:33 by mkarkaus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

void	ft_lstapp(t_list **alst, t_list *end)
{
	while ((*alst)->next)
		*alst = (*alst)->next;
	(*alst)->next = end;
}
