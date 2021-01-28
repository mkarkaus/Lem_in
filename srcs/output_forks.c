/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output_forks.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkarkaus <mkarkaus@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 10:23:15 by mkarkaus          #+#    #+#             */
/*   Updated: 2021/01/26 10:13:43 by mkarkaus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

void	del_bad_links(t_graph *maze, int fork, int best_out)
{
	int		path;
	int		i;

	path = -1;
	while (++path < maze->paths)
	{
		i = -1;
		while (++i < maze->max_level - 1)
			if (maze->route[path][i] == fork && maze->route[path][i + 1] != best_out)
				del_route(maze, path);
	}
}

void	handle_output_forks(t_graph *maze)
{
	t_node	*ptr;
	int		level;
	int		i;
	int		best;

	level = maze->max_level;
	while (level > 0)
	{
		i = 1;
		while (++i < maze->ver)
		{
			if (maze->array[i].bfs_level == level && maze->array[i].out > 1)
			{
				ptr = maze->array[i].head;
				best = ptr->v;
				ptr = ptr->next;
				while (ptr)
				{
					if (maze->array[ptr->v].dd < maze->array[best].dd)
						best = ptr->v;
					ptr = ptr->next;
				}
				del_bad_links(maze, i, best);
			}
		}
		level--;
	}
}
