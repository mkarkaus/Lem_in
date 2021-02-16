/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin_forks_in.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkarkaus <mkarkaus@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 14:36:48 by sreijola          #+#    #+#             */
/*   Updated: 2021/01/21 14:45:0 by mkarkaus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

void	del_route(t_graph *maze, int del)
{
	int		*temp;

	temp = maze->route[del];
	maze->route[del] = maze->route[maze->paths - 1];
	maze->route[maze->paths - 1] = temp;
	free(maze->route[maze->paths - 1]);
	maze->paths--;
}

void	fill_new_paths(t_graph *maze, int fork)
{
	t_node	*ptr;
	int		i;
	int		k;

	k = 0;
	i = 0;
	while (maze->route[k][0] != -1)
		k++;
	while (i < maze->max_level && maze->route[fork][i + 1] != -1)
		i++;
	ptr = maze->array[maze->route[fork][i]].head;
	while (k < maze->paths && ptr)
	{
		if (maze->been[ptr->v] == 0 \
		&& !(maze->flow[maze->route[fork][i]] == 1 && maze->flow[ptr->v] == 1))
		{
			if (maze->route[fork][i + 1] == -1)// If statement maybe useless
				maze->route[fork][i + 1] = ptr->v;
			else
			{
				ft_memcpy(maze->route[k], maze->route[fork], maze->max_level * sizeof(int));
				maze->route[k][i + 1] = ptr->v;
				if (ptr->v != 1)
					maze->been[ptr->v] = 1;
				k++;
			}
		}
		ptr = ptr->next;
	}
}

void	add_paths(int paths, int ***route, int prev, int max_level)
{
	int		**tmp;
	int		k;
	int		i;
	
	k = -1;
	tmp = ft_tabarr_malloc(paths, max_level + 1);
	while (++k < prev)
		ft_memcpy(tmp[k], (*route)[k], sizeof(int) * max_level);
	while (k < paths)
	{
		i = -1;
		while (++i < max_level)
			tmp[k][i] = -1;
		k++;
	}
	ft_tabarr_free(*route, prev);
	*route = tmp;
}

int		count_new_routes(t_graph *maze, int fork)
{
	t_node	*ptr;
	int		valid_routes;

	ptr = maze->array[fork].head;
	valid_routes = 0;
	while (ptr)
	{
		if (maze->been[ptr->v] != 1 \
			&& !(maze->flow[fork] == 1 && maze->flow[ptr->v] == 1))
		{
			if (ptr->v == 1)
				return (-1);
			valid_routes++;
		}
		ptr = ptr->next;
	}
	return (valid_routes);
}

void	update_been(t_graph *maze)
{
	int		row;
	int		i;

	row = 1;
	ft_bzero(maze->been, maze->ver * sizeof(int));
	while (row <= maze->sets[maze->max_sets][0][0])
	{
		i = 1;
		while (maze->sets[maze->max_sets][row][i] != 1)
		{
			maze->been[maze->sets[maze->max_sets][row][i]] = 1;
			i++;
		}
		row++;
	}
}

void	fill_visited(t_graph *maze, int row, int **visited)
{
	int		i;
	
	i = 0;
	*visited = (int *)ft_memalloc(sizeof(int) * maze->ver);
	while (maze->route[row][++i] != -1)
		(*visited)[maze->route[row][i]] = 1;
}

void	add_to_route(t_graph *maze, int prev_room, int *row, int len)
{
	int		ret;
	t_node	*ptr;

	ret = count_new_routes(maze, prev_room);
	ptr = maze->array[prev_room].head;
	while (ptr && (maze->been[ptr->v] == 1 \
		|| (maze->flow[prev_room] == 1 && maze->flow[ptr->v] == 1)))
		ptr = ptr->next;
	if (ret > 1)
	{
		maze->paths += (ret - 1);
		add_paths(maze->paths, &maze->route, maze->paths - (ret - 1), maze->max_level);
		fill_new_paths(maze, *row);
	}
	else if ((ret == 1 || ret == -1) && maze->been[ptr->v] != 1)
	{
		if (ret == -1)
			maze->route[*row][len] = 1;
		else
		{
			maze->route[*row][len] = ptr->v;
			maze->been[ptr->v] = 1;
		}
	}
	else
		del_route(maze, *row);
}

int		calculate_cost(int **set, int *new_route, int ants)
{
	int		prev_cost;
	int		path;
	int		cost;
	int		mod;

	path = 1;
	cost = new_route[0];
	prev_cost = set[0][1];
	while (path <= set[0][0])
	{
		cost += set[path][0];
		path++;
	}
	cost = (cost + ants) / path;
	mod = (cost + ants) % path;
	if ((cost < prev_cost || (cost == prev_cost && mod < set[0][2])))
	{
		set[0][1] = cost;
		set[0][2] = mod;
		return (1);
	}
	// ft_printf("len too much:%d\n", new_route[0]);
	return (0);
}

void	save_path(t_graph *maze, int *len, int i)
{
	int			**cur_set;
	
	cur_set = maze->sets[maze->max_sets];
	cur_set[0][0]++;
	cur_set[cur_set[0][0]] = ft_memalloc(maze->max_level * sizeof(int));
	cur_set[cur_set[0][0]] = ft_memcpy(cur_set[cur_set[0][0]], maze->route[i], *len * sizeof(int));
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
	while (++len < maze->max_level && maze->paths != 0)
	{
		i = -1;
		while (++i < maze->paths && maze->paths != 0)
			if (maze->route[i][len] == -1)
			{
				prev_room = maze->route[i][len - 1];
				if (maze->route[i][len - 1] == 1)
				{
					route_length(&maze->route[i]);
					if (calculate_cost(maze->sets[maze->max_sets], maze->route[i], ants))// we should use these values in picking the best set
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
