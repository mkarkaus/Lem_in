/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin_forks.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sreijola <sreijola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 15:19:54 by sreijola          #+#    #+#             */
/*   Updated: 2021/02/10 11:53:07 by sreijola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

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
		while (++len <= maze->max_level)
			maze->route[i][len] = -1;
		maze->route[i][0] = 0;
		maze->route[i][1] = ptr->v;
		maze->been[ptr->v] = 1;
		// del_allbutone(maze, 0, ptr->v, 0);
		// ft_pr_intarr(maze->route, 2, maze->max_level, 1);
		ptr = ptr->next;
		i++;
	}
	maze->paths = i;
}

// void	create_routes(t_graph *maze)
// {
// 	maze->been = (int *)ft_memalloc(maze->ver * sizeof(int));
// 	maze->route = ft_tabarr_malloc(maze->array[0].out, maze->max_level + 1);
// 	init_routes(maze);
	// ft_pr_intarr(maze->route, maze->paths, maze->max_level, 1);
	// handle_input_forks(maze);
	// ft_grapher(maze);
	// ft_pr_intarr(&maze->shrt, 1, maze->max_level, 1);
	// ft_printf("\n");
	// handle_output_forks(maze);
	// ft_tabarr_free(route, maze->array[0].out);
// }
