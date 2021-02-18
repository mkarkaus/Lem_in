/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_graph_edgeadd.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sreijola <sreijola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/06 13:29:18 by mkarkaus          #+#    #+#             */
/*   Updated: 2021/02/18 10:37:42 by sreijola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

void	ft_graph_edgeadd(t_graph *graph, int a, int b, int dir)
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
