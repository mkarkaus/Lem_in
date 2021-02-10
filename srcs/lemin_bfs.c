/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin_bfs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sreijola <sreijola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 12:22:11 by sreijola          #+#    #+#             */
/*   Updated: 2021/02/10 15:39:52 by sreijola         ###   ########.fr       */
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
		node = node->next;
		i++;
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

	row = 0;
	i = 1;
	while (row < maze->paths && (maze->route[row][2] == 1 || was_used(maze->used, maze->route[row])))
		row++;
	while (row != maze->paths && maze->route[row][i] != 1)
	{
		maze->flow[0] = 1;
		maze->flow[maze->route[row][i]] = 1;
		i++;
	}
	if (row != maze->paths)
	{
		maze->used[maze->used[0][0] + 1] = maze->route[row];
		maze->used[0][0]++;
	}
}

void	bfs_search_sets(t_graph *maze)
{
	create_set(maze);
	if (maze->paths > 0)
	{
		route_lengths(&maze->route, maze->paths);
		sort_routes(&maze->route, maze->paths);
	}
	ft_bzero(maze->flow, sizeof(int) * maze->ver);
	set_flow(maze);
}

void	find_route_sets(t_graph *maze, int ants)
{
	int	set;
	int path;
	int	i;

	maze->max_sets = -1;
	path = count_potential_paths(maze);
	init_sets(maze, path);
	while (++maze->max_sets < SEARCH_TIMES && maze->flow[0] == 1)
	{
		ft_bzero(maze->been, sizeof(int) * maze->ver);
		maze->route = ft_tabarr_malloc(path, maze->max_level);
		maze->paths = 0;
		init_routes(maze);
		bfs_search_sets(maze);
		maze->sets[maze->max_sets][0][0] = maze->paths;
		i = -1;
		while (++i < maze->paths)
			maze->sets[maze->max_sets][i + 1] = maze->route[i];
		free(maze->route);
		maze->route = NULL;
		ft_printf("SET CHANGED\n");
	}
	free(maze->used[0]);
	free(maze->used);
	free(maze->flow);
	free(maze->been);
}
