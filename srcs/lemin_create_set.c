/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin_create_set.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkarkaus <mkarkaus@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 14:36:48 by sreijola          #+#    #+#             */
/*   Updated: 2021/02/25 16:32:35 by mkarkaus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

void	route_length(int **route)
{
	int		i;

	i = 0;
	while ((*route)[i] != 1)
		i++;
	(*route)[0] = i;
}

void	update_been(t_graph *maze)
{
	int		row;
	int		i;

	row = 1;
	ft_bzero(maze->been, maze->ver * sizeof(int));
	while (row <= maze->set[0][0])
	{
		i = 1;
		while (maze->set[row][i] != 1)
		{
			maze->been[maze->set[row][i]] = 1;
			i++;
		}
		row++;
	}
}

int		calculate_cost(int **set, int *new_route, int ants)
{
	int		prev_cost;
	int		path;
	int		cost;
	int		mod;

	path = 1;
	cost = new_route[0] - 1;
	prev_cost = set[0][1];
	while (path <= set[0][0])
	{
		cost += (set[path][0] - 1);
		path++;
	}
	mod = (cost + ants) % path;
	cost = (cost + ants) / path;
	if ((cost < prev_cost || (cost == prev_cost && mod < set[0][2])))
	{
		set[0][1] = cost;
		set[0][2] = mod;
		return (1);
	}
	return (0);
}

void	save_path(t_graph *maze, int *len, int i)
{
	int	**set;
	int	row;

	set = maze->set;
	set[0][0]++;
	row = set[0][0];
	set[row] = ft_memalloc(LEN_MAX * sizeof(int));
	set[row] = ft_memcpy(set[row], maze->route[i], *len * sizeof(int));
	update_been(maze);
	ft_tabarr_free(maze->route, maze->paths);
	init_routes(maze);
	*len = 2;
}

void	create_set(t_graph *maze, int ants)
{
	int			prev_room;
	int			len;
	int			i;

	len = 1;
	while (++len < LEN_MAX && maze->paths != 0)
	{
		i = -1;
		while (++i < maze->paths && maze->paths != 0)
			if (maze->route[i][len] == -1)
			{
				if ((prev_room = maze->route[i][len - 1]) == 1)
				{
					route_length(&maze->route[i]);
					if (calculate_cost(maze->set, maze->route[i], ants))
						save_path(maze, &len, i);
					else
						return ;
				}
				else
					add_to_route(maze, prev_room, &i, len);
				i = -1;
			}
	}
}
