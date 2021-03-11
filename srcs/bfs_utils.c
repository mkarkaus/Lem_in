/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkarkaus <mkarkaus@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 15:19:54 by sreijola          #+#    #+#             */
/*   Updated: 2021/03/10 19:48:32 by mkarkaus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

int		count_potential_paths(t_graph *maze, int for_flow)
{
	int		i;
	t_node	*node;

	i = 0;
	node = maze->array[0].head;
	while (node != NULL)
	{
		if ((for_flow == -1 \
		|| (for_flow == 0 && node->flow == 1 && maze->been[node->v] == 0) \
		|| (for_flow == 1 && (node->flow == 2 || node->flow == -1)))
		&& maze->res[node->v] == 0 && !(node->v == 1 && maze->start_to_end))
			i++;
		node = node->next;
	}
	return (i);
}

void	init_sets(t_graph *maze)
{
	maze->been = (int *)ft_memalloc(sizeof(int) * maze->ver);
	maze->res = (int *)ft_memalloc(sizeof(int) * maze->ver);
	maze->start_to_end = 0;
	maze->best_set = (unsigned int **)ft_memalloc(sizeof(int *));
	maze->best_set[0] = (unsigned int *)ft_memalloc(sizeof(int) * 3);
	maze->best_set[0][1] = UINT_MAX;
	maze->best_set[0][2] = UINT_MAX;
}

void	init_routes(t_graph *maze, int for_flow)
{
	t_node		*ptr;
	int			i;

	ptr = maze->array[0].head;
	i = 0;
	maze->res[0] = 1;
	maze->route = ft_tabarr_malloc(count_potential_paths(maze, for_flow), \
		LEN_MAX);
	while (ptr)
	{
		if (((for_flow == 0 && ptr->flow == 1 && maze->been[ptr->v] == 0) \
			|| (for_flow == 1 && (ptr->flow == 2 || ptr->flow == -1)))
			&& !(ptr->v == 1 && maze->start_to_end))
		{
			maze->route[i][0] = 0;
			maze->route[i][1] = ptr->v;
			if (ptr->v != 1)
				maze->res[ptr->v] = 1;
			else
				maze->start_to_end = 1;
			i++;
		}
		ptr = ptr->next;
	}
	maze->paths = i;
}
