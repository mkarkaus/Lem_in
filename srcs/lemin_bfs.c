/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin_bfs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sreijola <sreijola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 12:22:11 by sreijola          #+#    #+#             */
/*   Updated: 2021/02/09 13:08:33 by sreijola         ###   ########.fr       */
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

void	init_sets(t_graph *maze, int path)
{
	int		i;

	i = 0;
	maze->used = (int **)ft_memalloc(sizeof(int *) * (SEARCH_TIMES + 1));
	maze->used[0] = (int *)ft_memalloc(sizeof(int));
	maze->used[0][0] = 0;

	maze->flow = (int *)ft_memalloc(sizeof(int) * maze->ver);
	ft_bzero(maze->flow, sizeof(int) * maze->ver);
	maze->been = (int *)ft_memalloc(sizeof(int) * maze->ver);
	maze->sets = (int ***)ft_memalloc(sizeof(int **) * SEARCH_TIMES);// 3 stands for 3 sets
	while (i < SEARCH_TIMES)
	{
		maze->sets[i] = (int **)ft_memalloc(sizeof(int *) * (path + 1)); //koska tallennetaan vain lyhin reitti ja sen määrä 0:teen
		maze->sets[i][0] = (int *)ft_memalloc(sizeof(int));
		maze->sets[i][0][0] = 0;
		i++;
	}
}

void	find_route_sets(t_graph *maze, int ants)
{
	int	set;
	int path;
	int	i;

	set = 0;
	path = count_potential_paths(maze);
	ft_pr_intarr(maze->route, maze->paths, maze->max_level, 1);
	init_sets(maze, path);
	while (set < SEARCH_TIMES)
	{
		ft_bzero(maze->been, sizeof(int) * maze->ver);
		maze->route = ft_tabarr_malloc(path, maze->max_level + 1);
		maze->paths = 0;
		init_routes(maze);
		bfs_search_sets(maze);//, set == 0);
		maze->sets[set][0][0] = maze->paths;
		ft_printf("%d\n", maze->paths);
		ft_pr_intarr(maze->route, maze->paths, 10, 1);
		i = -1;
		while (++i < maze->paths)
			maze->sets[set][i + 1] = maze->route[i];
		maze->route = NULL;
		set++;
	}
}
