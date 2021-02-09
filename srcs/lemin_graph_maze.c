/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin_graph_maze.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sreijola <sreijola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/06 13:28:46 by mkarkaus          #+#    #+#             */
/*   Updated: 2021/02/09 12:51:07 by sreijola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

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
				if (ptr[node->v].bfs_level == -1 \
					&& !ft_tabint_find(*queue, node->v, maze->ver))
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
