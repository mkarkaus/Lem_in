/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin_bfs_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sreijola <sreijola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 15:19:54 by sreijola          #+#    #+#             */
/*   Updated: 2021/02/12 17:16:13 by sreijola         ###   ########.fr       */
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

void	route_length(int **route)
{
	int		i;

	i = 0;
	while ((*route)[i] != 1)
		i++;
	(*route)[0] = i;
}

void	init_sets(t_graph *maze)
{
	int		i;

	i = 0;
	maze->used = (int **)ft_memalloc(sizeof(int *) * (SEARCH_TIMES + 1));
	maze->used[0] = (int *)ft_memalloc(sizeof(int));
	maze->used[0][0] = 0;

	maze->flow = (int *)ft_memalloc(sizeof(int) * maze->ver);
	maze->flow[0] = 1;
	maze->been = (int *)ft_memalloc(sizeof(int) * maze->ver);
	maze->sets = (int ***)ft_memalloc(sizeof(int **) * SEARCH_TIMES);// 3 stands for 3 sets
	while (i < SEARCH_TIMES)
	{
		maze->sets[i] = (int **)ft_memalloc(sizeof(int *) * (count_potential_paths(maze) + 1)); //koska tallennetaan vain lyhin reitti ja sen määrä 0:teen
		maze->sets[i][0] = (int *)ft_memalloc(sizeof(int) * 3);
		maze->sets[i][0][1] = INT_MAX;
		maze->sets[i][0][2] = INT_MAX;
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
	maze->route = ft_tabarr_malloc(count_potential_paths(maze), maze->max_level);
	while (ptr) //init routes with links from start and cross-check
	{
		if (maze->been[ptr->v] == 0)
		{
			len = -1;
			while (++len < maze->max_level)
				maze->route[i][len] = -1;
			maze->route[i][0] = 0;
			maze->route[i][1] = ptr->v;
			maze->been[ptr->v] = 1;
			i++;
		}
		ptr = ptr->next;
	}
	maze->paths = i;
}
