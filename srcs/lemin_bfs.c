/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin_bfs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkarkaus <mkarkaus@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 12:22:11 by sreijola          #+#    #+#             */
/*   Updated: 2021/02/25 16:37:59 by mkarkaus         ###   ########.fr       */
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
	while (row < maze->set[0][0] + 1 \
			&& (maze->set[row][2] == 1 \
			|| was_used(maze->used, maze->set[row])))
		row++;
	while (row != maze->set[0][0] + 1 \
			&& maze->set[row][i] != 1)
	{
		maze->flow[0] = 1;
		maze->flow[maze->set[row][i]] = 1;
		i++;
	}
	if (row != maze->set[0][0] + 1)
	{
		ft_memcpy(maze->used[maze->used[0][0] + 1], maze->set[row], \
			(maze->set[row][0] + 1) * sizeof(int));
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
	maze->set = (int **)ft_memalloc(sizeof(int *) * \
					(count_potential_paths(maze) + 1));
	maze->set[0] = (int *)ft_memalloc(sizeof(int) * 3);
	maze->set[0][1] = INT_MAX;
	maze->set[0][2] = INT_MAX;
	init_routes(maze);
	create_set(maze, ants);
	if (maze->set[0][0] > 0)
		sort_routes(&maze->set, maze->set[0][0] + 1);
	ft_bzero(maze->flow, sizeof(int) * maze->ver);
	set_flow(maze);
}

void	find_route_sets(t_graph *maze, int ants)
{
	int		set_count;

	set_count = -1;
	init_sets(maze);
	while (++set_count < SEARCH_TIMES && maze->flow[0] == 1)
	{
		ft_bzero(maze->been, sizeof(int) * maze->ver);
		maze->start_to_end = 0;
		bfs_search_sets(maze, ants);
		if (maze->best_set[0][1] > maze->set[0][1] \
			|| (maze->best_set[0][1] == maze->set[0][1] \
			&& maze->best_set[0][2] > maze->set[0][2]))
		{
			ft_tabarr_free(maze->best_set, maze->best_set[0][0] + 1);
			maze->best_set = maze->set;
		}
		else
			ft_tabarr_free(maze->set, maze->set[0][0] + 1);
		ft_tabarr_free(maze->route, maze->paths);
	}
	free(maze->flow);
	free(maze->been);
}
