/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graph_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkarkaus <mkarkaus@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/26 12:05:41 by mkarkaus          #+#    #+#             */
/*   Updated: 2021/02/26 13:49:53 by mkarkaus         ###   ########.fr       */
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

void	ft_graph_free(t_graph *graph)
{
	t_node	*tmp;

	while (--graph->ver >= 0)
	{
		while (graph->array[graph->ver].head)
		{
			tmp = graph->array[graph->ver].head->next;
			free(graph->array[graph->ver].head);
			graph->array[graph->ver].head = tmp;
		}
	}
	free(graph->array);
	free(graph);
}

t_graph	*ft_graph_new(int vertices)
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

t_node	*ft_graph_nodenew(int dest_ver)
{
	t_node	*new;

	new = ft_memalloc(sizeof(t_node));
	new->v = dest_ver;
	new->next = NULL;
	return (new);
}

void	ft_graph_print(t_graph *graph, char **name)
{
	t_node	*ptr;
	int		i;

	i = -1;
	while (++i < graph->ver)
	{
		ptr = graph->array[i].head;
		ft_printf("[ %d ][%s]", i, name[i]);
		while (ptr != NULL)
		{
			ft_printf(" -> %d", ptr->v);
			ptr = ptr->next;
		}
		ft_printf("\n");
	}
}
