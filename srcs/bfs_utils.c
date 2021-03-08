/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkarkaus <mkarkaus@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 15:19:54 by sreijola          #+#    #+#             */
/*   Updated: 2021/03/08 17:53:14 by mkarkaus         ###   ########.fr       */
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
		if (maze->been[node->v] == 0 && maze->res[node->v] == 0 \
		&& !(node->v == 1 && maze->start_to_end))
			i++;
		node = node->next;
	}
	return (i);
}

void	init_sets(t_graph *maze)
{
	maze->used = (unsigned int **)ft_tabarr_malloc(SEARCH_TIMES + 1, LEN_MAX);
	maze->flow = (int *)ft_memalloc(sizeof(int) * maze->ver);
	maze->flow[0] = 1;
	maze->been = (int *)ft_memalloc(sizeof(int) * maze->ver);
	maze->res = (int *)ft_memalloc(sizeof(int) * maze->ver);
	maze->start_to_end = 0;
	maze->best_set = (unsigned int **)ft_memalloc(sizeof(int *));
	maze->best_set[0] = (unsigned int *)ft_memalloc(sizeof(int) * 3);
	maze->best_set[0][1] = UINT_MAX;
	maze->best_set[0][2] = UINT_MAX;
}

void	init_routes(t_graph *maze)
{
	t_node		*ptr;
	int			i;
	// int			len;

	ptr = maze->array[0].head;
	i = 0;
	maze->res[0] = 1;
	maze->route = ft_tabarr_malloc(count_potential_paths(maze), LEN_MAX);
	while (ptr)
	{
		if (maze->been[ptr->v] == 0 && !(ptr->v == 1 && maze->start_to_end))
		{
			// len = -1;

			// while (++len < LEN_MAX)
			// 	maze->route[i][len] = -1;
			maze->route[i][0] = 0;
			maze->route[i][1] = ptr->v;
			maze->res[ptr->v] = 1;
			if (ptr->v == 1)
				maze->start_to_end = 1;
			i++;
		}
		ptr = ptr->next;
	}
	maze->paths = i;
}
