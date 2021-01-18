/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin_forks.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sreijola <sreijola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 15:19:54 by sreijola          #+#    #+#             */
/*   Updated: 2021/01/18 17:24:32 by sreijola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"


void	del_bad_links(t_graph **maze, int fork, int best_out)
{
	int		path;
	int		i;

	path = -1;
	while (++path < (*maze)->paths)
	{
		i = -1;
		while (++i < (*maze)->max_level - 1)
			if (((*maze)->route)[path][i] == fork && ((*maze)->route)[path][i + 1] != best_out)
				del_route(maze, path);
	}
}

void	handle_output_forks(t_graph **maze)
{
	t_node	*ptr;
	int		i;
	int		rm;

	i = 1;
	while (++i < (*maze)->ver)
	{
		if ((*maze)->array[i].out > 1)
		{
			ptr = (*maze)->array[i].head;
			rm = ptr->v;
			ptr = ptr->next;
			while (ptr)
			{
				if ((*maze)->array[ptr->v].dd < (*maze)->array[rm].dd)
					rm = ptr->v;
				ptr = ptr->next;
			}
			del_bad_links(maze, i, rm);
		}
	}
}

void	init_routes(t_graph **maze)
{
	t_node		*ptr;
	int			i;
	int			len;

	ptr = (*maze)->array[0].head;
	i = 0;
	while (ptr) //init routes with links from start and cross-check and del them from other rooms
	{
		len = -1;
		while (++len <= (*maze)->max_level)
			(*maze)->route[i][len] = -1;
		(*maze)->route[i][0] = 0;
		(*maze)->route[i][1] = ptr->v;
		del_allbutone(maze, 0, ptr->v, 0);
		ft_pr_intarr((*maze)->route, (*maze)->paths, (*maze)->max_level, 1);
		ptr = ptr->next;
		i++;
	}
	(*maze)->paths = i;
}

void	create_routes(t_graph **maze)
{
	(*maze)->route = ft_tabarr_malloc((*maze)->array[0].out, (*maze)->max_level + 1);
	(*maze)->been = (int *)ft_memalloc((*maze)->ver * sizeof(int));
	ft_grapher(*maze);
	init_routes(maze);
	handle_input_forks(maze);
	ft_printf("input forks done\n");
	ft_printf("\n");
	handle_output_forks(maze);
	ft_printf("output forks done\n");
	// ft_grapher(*maze);
	// ft_tabarr_free(route, (*maze)->array[0].out);
}
