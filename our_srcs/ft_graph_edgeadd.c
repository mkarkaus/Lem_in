/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_graph_edgeadd.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkarkaus <mkarkaus@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/06 13:29:18 by mkarkaus          #+#    #+#             */
/*   Updated: 2020/10/06 13:32:15 by mkarkaus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

void	ft_graph_edgeadd(t_graph *graph, int a, int b, int dir)// former add_edge
{
	t_node	*node;

	if (dir == 0 || dir == 1)
	{
		node = ft_graph_nodenew(b);
		node->next = graph->array[a].head;
		graph->array[a].head = node;
	}
	if (dir == 0 || dir == 2)
	{
		node = ft_graph_nodenew(a);
		node->next = graph->array[b].head;
		graph->array[b].head = node;
	}
}
