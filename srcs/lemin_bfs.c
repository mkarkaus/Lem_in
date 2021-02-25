/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin_bfs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkarkaus <mkarkaus@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 12:22:11 by sreijola          #+#    #+#             */
/*   Updated: 2021/02/25 10:43:48 by mkarkaus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

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

void	sort_routes(int ***route, int max_paths)
{
	int		row;
	int		swapped;
	int		*temp;

	swapped = 1;
	while (swapped == 1)
	{
		swapped = 0;
		row = 1;
		while (row + 1 < max_paths)
		{
			if ((*route)[row][0] > (*route)[row + 1][0])
			{
				temp = (*route)[row];
				(*route)[row] = (*route)[row + 1];
				(*route)[row + 1] = temp;
				swapped = 1;
			}
			row++;
		}
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
		maze->start_to_end = 0;
		init_routes(maze);
		bfs_search_sets(maze, ants);
		if (maze->best_set[0][1] > maze->sets[maze->max_sets][0][1] \
				|| (maze->best_set[0][1] == maze->sets[maze->max_sets][0][1] \
				&& maze->best_set[0][2] > maze->sets[maze->max_sets][0][2]))
			maze->best_set = maze->sets[maze->max_sets];
		ft_tabarr_free(maze->route, maze->paths);
		maze->route = NULL;
	}
	ft_pr_intarr(maze->best_set, maze->best_set[0][0] + 1, 40, 1);
	free(maze->used[0]);
	free(maze->used);
	free(maze->flow);
	free(maze->been);
}
