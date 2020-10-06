/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_graph_nodenew.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkarkaus <mkarkaus@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/06 13:29:47 by mkarkaus          #+#    #+#             */
/*   Updated: 2020/10/06 13:29:50 by mkarkaus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

t_node	*ft_graph_nodenew(int dest_ver)
{
	t_node	*new;

	new = ft_memalloc(sizeof(t_node));
	new->v = dest_ver;
	new->next = NULL;
	return (new);
}
