/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkarkaus <mkarkaus@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 12:22:11 by sreijola          #+#    #+#             */
/*   Updated: 2021/03/10 19:50:22 by mkarkaus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

void	sort_routes(unsigned int ***route, int max_paths)
{
	int				row;
	int				swapped;
	unsigned int	*temp;

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

int		bfs_search_sets(t_graph *maze, unsigned int ants)
{
	maze->set = (unsigned int **)ft_memalloc(sizeof(unsigned int *) * \
					(count_potential_paths(maze, -1) + 1));
	maze->set[0] = (unsigned int *)ft_memalloc(sizeof(unsigned int) * 3);
	maze->set[0][1] = UINT_MAX;
	maze->set[0][2] = UINT_MAX;
	init_routes(maze, 1);
	maze->flow_set = 0;
	search_flow(maze);
	ft_bzero(maze->res, sizeof(int) * maze->ver);
	ft_arr_free((void **)maze->route, maze->paths);
	maze->start_to_end = 0;
	init_routes(maze, 0);
	create_set(maze, ants);
	if (maze->set[0][0] > 0)
	{
		sort_routes(&maze->set, maze->set[0][0] + 1);
		return (0);
	}
	else
		return (-1);
}

int		find_route_sets(t_graph *maze, unsigned int ants)
{
	int		set_count;

	set_count = 0;
	init_sets(maze);
	maze->flow_set = 1;
	while (maze->flow_set == 1)
	{
		ft_bzero(maze->res, sizeof(int) * maze->ver);
		ft_bzero(maze->been, sizeof(int) * maze->ver);
		maze->start_to_end = 0;
		if (bfs_search_sets(maze, ants) == -1 && set_count == 0)
			return (-5);
		if (maze->best_set[0][1] > maze->set[0][1] \
			|| (maze->best_set[0][1] == maze->set[0][1] \
			&& maze->best_set[0][2] > maze->set[0][2]))
		{
			ft_arr_free((void **)maze->best_set, maze->best_set[0][0] + 1);
			maze->best_set = maze->set;
		}
		else
			ft_arr_free((void **)maze->set, maze->set[0][0] + 1);
		ft_arr_free((void **)maze->route, maze->paths);
		set_count++;
	}
	return (0);
}
