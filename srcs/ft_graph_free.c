/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_graph_free.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sreijola <sreijola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/06 19:08:33 by sreijola          #+#    #+#             */
/*   Updated: 2020/10/07 11:20:59 by sreijola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"


void	ft_graph_free(t_graph *graph)
{
	t_node	*tmp;

	while (--graph->ver >= 0) //(vai tässä --graph->ver)
	{
		while (graph->array[graph->ver].head)
		{
			tmp = graph->array[graph->ver].head;
			graph->array[graph->ver].head = graph->array[graph->ver].head->next;
			free(tmp);
		}
	}
	free(graph->array);
	free(graph);
}
