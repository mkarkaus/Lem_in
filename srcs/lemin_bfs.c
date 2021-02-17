/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin_bfs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sreijola <sreijola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 12:22:11 by sreijola          #+#    #+#             */
/*   Updated: 2021/02/17 12:35:35 by sreijola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

int		count_potential_paths(t_graph *maze)
{
	int		i;
	t_node	*node;

	i = 0;
	node = maze->array[0].head;
	while (node != NULL)
	{
		if (maze->been[node->v] == 0 \
		&& !(node->v == 1 && maze->start_to_end_found))
			i++;
		node = node->next;
	}
	return (i);
}

int		was_used(int **used, int *route)
{
	int		i;
	int		row;

	row = 1;
	while (row <= used[0][0])
	{
		i = 1;
		while (used[row][i] == route[i])
		{
			if (used[row][i] == 1 && route[i] == 1)
				return (1);
			i++;
		}
		row++;
	}
	return (0);
}

void	set_flow(t_graph *maze)
{
	int		i;
	int		row;

	row = 1;
	i = 1;
	while (row < maze->sets[maze->max_sets][0][0] + 1 \
			&& (maze->sets[maze->max_sets][row][2] == 1 \
			|| was_used(maze->used, maze->sets[maze->max_sets][row])))
		row++;
	while (row != maze->sets[maze->max_sets][0][0] + 1 \
			&& maze->sets[maze->max_sets][row][i] != 1)
	{
		maze->flow[0] = 1;
		maze->flow[maze->sets[maze->max_sets][row][i]] = 1;
		i++;
	}
	if (row != maze->sets[maze->max_sets][0][0] + 1)
	{
		maze->used[maze->used[0][0] + 1] = maze->sets[maze->max_sets][row];
		maze->used[0][0]++;
	}
}

void	bfs_search_sets(t_graph *maze, int ants)
{
	int		max_paths;
	
	create_set(maze, ants);
	max_paths = maze->sets[maze->max_sets][0][0] + 1;
	if (maze->sets[maze->max_sets][0][0] > 0)
		sort_routes(&maze->sets[maze->max_sets], max_paths);
	else
		maze->max_sets--;
	ft_bzero(maze->flow, sizeof(int) * maze->ver);
	set_flow(maze);
}

void	find_route_sets(t_graph *maze, int ants)
{
	maze->max_sets = -1;
	init_sets(maze);
	while (++maze->max_sets < SEARCH_TIMES && maze->flow[0] == 1)
	{
		ft_bzero(maze->been, sizeof(int) * maze->ver);
		maze->start_to_end_found = 0;
		init_routes(maze);
		bfs_search_sets(maze, ants);
		// ft_pr_intarr(maze->route, );
		ft_tabarr_free(maze->route, maze->paths);
		maze->route = NULL;
		ft_printf("SET CHANGED\n");
	}
	free(maze->used[0]);
	free(maze->used);
	free(maze->flow);
	free(maze->been);
}
