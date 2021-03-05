/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkarkaus <mkarkaus@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 12:22:11 by sreijola          #+#    #+#             */
/*   Updated: 2021/03/05 12:49:26 by mkarkaus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

int		was_used(unsigned int **used, unsigned int *route)
{
	int				i;
	unsigned int	row;

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
	int				i;
	unsigned int	row;

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
					(count_potential_paths(maze) + 1));
	maze->set[0] = (unsigned int *)ft_memalloc(sizeof(unsigned int) * 3);
	maze->set[0][1] = UINT_MAX;
	maze->set[0][2] = UINT_MAX;
	init_routes(maze);
	create_set(maze, ants);
	if (maze->set[0][0] > 0)
		sort_routes(&maze->set, maze->set[0][0] + 1);
	else
		return (-1);
	ft_bzero(maze->flow, sizeof(int) * maze->ver);
	set_flow(maze);
	return (0);
}

int		find_route_sets(t_graph *maze, unsigned int ants)
{
	int		set_count;

	set_count = -1;
	init_sets(maze);
	while (++set_count < SEARCH_TIMES && maze->flow[0] == 1)
	{
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
	}
	free(maze->flow);
	free(maze->been);
	return (0);
}
