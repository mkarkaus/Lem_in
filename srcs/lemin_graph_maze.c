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
	if (ah->maze->array[0].dd == -1)
		return (-1);
	return (0);
}
