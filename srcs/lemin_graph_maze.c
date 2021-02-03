/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin_graph_maze.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkakksus <mkakksus@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/06 13:28:46 by mkarkaus          #+#    #+#             */
/*   Updated: 2021/01/11 14:11:417 bymkakksusa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

void	ft_grapher(t_graph *graph)
{
	t_node	*ptr;
	int		i;

	i = -1;
	while (++i < graph->ver)
	{
		ptr = graph->array[i].head;
		ft_printf("[ %d ] (dd:%d, level:%d, in:%d, out:%d)", i, graph->array[i].dd, graph->array[i].bfs_level, graph->array[i].in, graph->array[i].out);
		while (ptr != NULL)
		{
			ft_printf(" -> %d", ptr->v);
			ptr = ptr->next;
		}
		ft_printf("\n");
	}
}

void	remake_queue(t_graph *maze, int **queue, int only_clear, int *been)
{
	int			i;
	int			k;
	int			*temp;
	t_node		*node;
	t_alhead	*ptr;

	i = -1;
	temp = ft_memalloc(maze->ver * sizeof(int));
	ft_memcpy(temp, *queue, maze->ver * sizeof(int));
	while (++i < maze->ver)
		(*queue)[i] = -1;
	i = 0;
	k = 0;
	ptr = maze->array;
	if (only_clear == 0)
	{
		while (temp[k] != -1)
		{
			node = ptr[temp[k]].head;
			while (node != NULL)
			{
				if ((ptr[node->v].dd == -1 && !ft_tabint_find(*queue, node->v, maze->ver) && been == NULL) \
					|| (been != NULL && !ft_tabint_find(been, node->v, maze->ver) && ptr[node->v].dd != -3))
					(*queue)[i++] = node->v;
				node = node->next;
			}
			k++;
		}
	}
	free(temp);
}

void	fill_distances(t_hill *ah)
{
	int			*q;
	int			i;
	int			dis;

	dis = 0;
	i = -1;
	q = ft_memalloc(ah->rooms * sizeof(int));
	remake_queue(ah->maze, &q, 1, NULL);
	q[0] = 1;
	while (++i < ah->rooms)
		ah->maze->array[i].dd = -1;
	while (q[0] > -1)
	{
		i = -1;
		while (q[++i] != -1)
			ah->maze->array[q[i]].dd = dis;
		remake_queue(ah->maze, &q, 0, NULL);
		dis++;
	}
	free(q);
}

void	requeue(t_graph *maze, int **queue, int only_clear)
{
	int			i;
	int			k;
	int			*temp;
	t_node		*node;
	t_alhead	*ptr;

	i = -1;
	temp = (int *)ft_memalloc(maze->ver * sizeof(int));
	ft_memcpy(temp, *queue, maze->ver * sizeof(int));
	while (++i < maze->ver)
		(*queue)[i] = -1;
	i = 0;
	k = 0;
	ptr = maze->array;
	if (only_clear == 0)
	{
		while (temp[k] != -1)
		{
			node = ptr[temp[k]].head;
			while (node != NULL)
			{
				if (ptr[node->v].bfs_level == -1 && !ft_tabint_find(*queue, node->v, maze->ver))
					(*queue)[i++] = node->v;
				node = node->next;
			}
			k++;
		}
	}
	free(temp);
	// temp = NULL;
}

void	bfs_levels(t_graph *maze)
{
	int			*q;
	int			i;
	int			level;

	level = 0;
	i = -1;
	q = (int *)ft_memalloc(maze->ver * sizeof(int));
	// ft_printf("maze->ver:%d\n", maze->ver);
	requeue(maze, &q, 1);
	q[0] = 0;
	while (++i < maze->ver)
	{
		maze->array[i].in = 0;
		maze->array[i].out = 0;
		maze->array[i].bfs_level = -1;
	}
	while (q[0] > -1)
	{
		i = -1;
		while (q[++i] != -1)
			maze->array[q[i]].bfs_level = level;
		requeue(maze, &q, 0);
		level++;
	}
	free(q);
	maze->array[1].bfs_level = INT_MAX;
	// maze->max_level = (level + 1) * 2;
	maze->max_level = 500;
}

int		*find_shortest_route(t_graph *maze)
{
	t_node	*ptr;
	int		*shortest;
	int		room;
	int		i;

	// ft_printf("max_level:%d\n", maze->max_level);
	shortest = (int *)ft_memalloc(maze->max_level * sizeof(int));
	// ft_printf("maze->max_level:%d\n", maze->max_level);
	i = 1;
	shortest[0] = 0;
	room = 0;
	while (room != 1)
	{
		ptr = maze->array[room].head;
		while (ptr)
		{
			if (maze->array[room].dd >= maze->array[ptr->v].dd)
				room = ptr->v;
			ptr = ptr->next;
		}
		shortest[i++] = room;
	}
	while (i < maze->max_level)
	{
		shortest[i] = room;
		i++;
	}
	return (shortest);
}

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

void	set_flow(int **route, int paths, int **flow)
{
	int		i;
	int		row;

	row = 0;
	i = 1;
	while (row < paths && route[row][2] == 1)
		row++;
	while (row != paths && route[row][i] != 1 && route[row][i + 1] != 1)
	{
		// ft_pr_intarr(route, paths, 3, 1);
		(*flow)[route[row][i]] = route[row][i + 1];
		(*flow)[route[row][i + 1]] = route[row][i];
		i++;
	}
}

void	bfs_search_sets(t_graph *maze, int del_all_others)
{
	int		i;
	int		max_paths;

	create_set(maze);
	if (maze->paths > 0)
	{
		route_lengths(&maze->route, maze->paths);
		sort_routes(&maze->route, maze->paths);
	}
	// ft_bzero(maze->flow, sizeof(int) * maze->ver);
	set_flow(maze->route, maze->paths, &maze->flow);
}

void	init_sets(t_graph *maze, int path)
{
	int		i;

	i = 0;
	maze->flow = (int *)ft_memalloc(sizeof(int) * maze->ver);
	ft_bzero(maze->flow, sizeof(int) * maze->ver);
	maze->been = (int *)ft_memalloc(sizeof(int) * maze->ver);
	maze->sets = (int ***)ft_memalloc(sizeof(int **) * 30);// 3 stands for 3 sets
	while (i < 30)
	{
		maze->sets[i] = (int **)ft_memalloc(sizeof(int *) * (path + 1)); //koska tallennetaan vain lyhin reitti ja sen määrä 0:teen
		maze->sets[i][0] = (int *)ft_memalloc(sizeof(int));
		maze->sets[i][0][0] = 0;
		i++;
	}
}

int		sum_lens(int paths, int **route)
{
	int ret;
	
	ret = 0;
	while (--paths >= 0)
		ret += route[paths][0];
	return (ret);
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
	while (set < 30)
	{
		ft_bzero(maze->been, sizeof(int) * maze->ver);
		maze->route = ft_tabarr_malloc(path, maze->max_level + 1);
		init_routes(maze);
		bfs_search_sets(maze, set == 0);
		maze->sets[set][0][0] = maze->paths;
		maze->sets[set][0][1] = ((sum_lens(maze->paths, maze->route) + ants) / maze->paths) - 1;
		i = -1;
		while (++i < maze->paths)
			maze->sets[set][i + 1] = maze->route[i];
		maze->route = NULL;
		set++;
		ft_printf("SET CHANGED\n");
	}
}

int		graph_maze(t_hill *ah)
{
	int		i;

	i = -1;
	ah->maze = ft_graph_new(ah->rooms);
	while (++i < ah->links)
		ft_graph_edgeadd(ah->maze, ah->link[i][0], ah->link[i][1], 0);
	fill_distances(ah);
	bfs_levels(ah->maze);
	// ft_graph_print(ah->maze, ah->name);
	find_route_sets(ah->maze, ah->ants);


	// i = -1;
	// while (++i < 3)
	// {
	// 	ft_printf("paths: %d\n", ah->maze->sets[i][0][0]);
	// 	ft_pr_intarr(ah->maze->sets[i] + 1, ah->maze->sets[i][0][0], ah->maze->max_level, 1);
	// 	ft_printf("\n");
	// }
	// exit(1);


	// del_twoway(ah->maze);
	// del_zero_inputs(ah->maze);// Not sure if works yet, check later
	// del_zero_outputs(ah->maze);
	// ft_printf("\n");
	// ft_pr_intarr(&ah->maze->shrt, 1, ah->maze->max_level, 1);
	// ah->maze->shrt = find_shortest_route(ah->maze);
	// create_routes(ah->maze);
	
	// ft_graph_print(ah->maze, ah->name);
	if (ah->maze->array[0].dd == -1)
		return (-1);
	return (0);
}
