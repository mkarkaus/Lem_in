/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_graph_print.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sreijola <sreijola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/06 13:35:45 by mkarkaus          #+#    #+#             */
/*   Updated: 2021/02/18 15:38:38 by sreijola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

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
