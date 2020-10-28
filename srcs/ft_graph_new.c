/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_graph_new.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sreijola <sreijola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/06 13:28:39 by mkarkaus          #+#    #+#             */
/*   Updated: 2020/10/27 15:51:31 by sreijola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

t_graph		*ft_graph_new(int vertices)// formerly known as create_graph()
{
	t_graph		*graph;
	int			i;

	i = -1;
	graph = (t_graph *)ft_memalloc(sizeof(t_graph));
	graph->ver = vertices;
	graph->array = (t_alhead *)ft_memalloc(vertices * sizeof(t_alhead));
	while (++i < vertices)
		graph->array[i].head = NULL;
	return (graph);
}
