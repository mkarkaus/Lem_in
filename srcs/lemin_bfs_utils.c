/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin_bfs_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sreijola <sreijola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 15:19:54 by sreijola          #+#    #+#             */
/*   Updated: 2021/02/10 15:30:19 by sreijola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

void	sort_routes(int ***route, int max_paths)
{
	int		row;
	int		swapped;
	int		*temp;

	swapped = 1;
	while (swapped == 1)
	{
		swapped = 0;
		row = 0;
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

void	route_lengths(int ***route, int max_paths)
{
	int		i;
	int		row;

	row = 0;
	while (row < max_paths)
	{
		i = 0;
		while ((*route)[row][i] != 1)
			i++;
		(*route)[row][0] = i;
		row++;
	}
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
	maze->flow[0] = 1;
	maze->been = (int *)ft_memalloc(sizeof(int) * maze->ver);
	maze->sets = (int ***)ft_memalloc(sizeof(int **) * SEARCH_TIMES);// 3 stands for 3 sets
	while (i < SEARCH_TIMES)
	{
		maze->sets[i] = (int **)ft_memalloc(sizeof(int *) * (path + 1)); //koska tallennetaan vain lyhin reitti ja sen määrä 0:teen
		maze->sets[i][0] = (int *)ft_memalloc(sizeof(int));
		i++;
	}
}

void	init_routes(t_graph *maze)
{
	t_node		*ptr;
	int			i;
	int			len;

	ptr = maze->array[0].head;
	i = 0;
	maze->been[0] = 1;
	while (ptr) //init routes with links from start and cross-check and del them from other rooms
	{
		len = -1;
		while (++len < maze->max_level)
			maze->route[i][len] = -1;
		maze->route[i][0] = 0;
		maze->route[i][1] = ptr->v;
		maze->been[ptr->v] = 1;
		ptr = ptr->next;
		i++;
	}
	maze->paths = i;
}
