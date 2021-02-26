/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin_build_route.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkarkaus <mkarkaus@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 16:15:28 by sreijola          #+#    #+#             */
/*   Updated: 2021/02/26 11:48:58 by mkarkaus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

void	del_route(t_graph *maze, int del)
{
	int		*temp;

	temp = maze->route[del];
	maze->route[del] = maze->route[maze->paths - 1];
	maze->route[maze->paths - 1] = temp;
	free(maze->route[maze->paths - 1]);
	maze->paths--;
}

void	fill_new_paths(t_graph *maze, int fork, int k, int i)
{
	t_node	*ptr;

	while (i < LEN_MAX && maze->route[fork][i + 1] != -1)
		i++;
	ptr = maze->array[maze->route[fork][i]].head;
	while (k < maze->paths && ptr)
	{
		if (maze->been[ptr->v] == 0 \
		&& !(maze->flow[maze->route[fork][i]] == 1 && maze->flow[ptr->v] == 1))
		{
			if (maze->route[fork][i + 1] == -1)
				maze->route[fork][i + 1] = ptr->v;
			else
			{
				ft_memcpy(maze->route[k], maze->route[fork], \
					LEN_MAX * sizeof(int));
				maze->route[k][i + 1] = ptr->v;
				if (ptr->v != 1)
					maze->been[ptr->v] = 1;
				k++;
			}
		}
		ptr = ptr->next;
	}
}

void	add_paths(int paths, int ***route, int prev, int max_level)
{
	int		**tmp;
	int		k;
	int		i;

	k = -1;
	tmp = ft_tabarr_malloc(paths, max_level + 1);
	while (++k < prev)
		ft_memcpy(tmp[k], (*route)[k], sizeof(int) * max_level);
	while (k < paths)
	{
		i = -1;
		while (++i < max_level)
			tmp[k][i] = -1;
		k++;
	}
	ft_tabarr_free(*route, prev);
	*route = NULL;
	*route = tmp;
}

int		count_new_routes(t_graph *maze, int fork)
{
	t_node	*ptr;
	int		valid_routes;

	ptr = maze->array[fork].head;
	valid_routes = 0;
	while (ptr)
	{
		if (maze->been[ptr->v] != 1 \
			&& !(maze->flow[fork] == 1 && maze->flow[ptr->v] == 1))
		{
			if (ptr->v == 1)
				return (-1);
			valid_routes++;
		}
		ptr = ptr->next;
	}
	return (valid_routes);
}

void	add_to_route(t_graph *maze, int prev_room, int *row, int len)
{
	int		ret;
	t_node	*ptr;

	ret = count_new_routes(maze, prev_room);
	ptr = maze->array[prev_room].head;
	while (ptr && (maze->been[ptr->v] == 1 \
		|| (maze->flow[prev_room] == 1 && maze->flow[ptr->v] == 1)))
		ptr = ptr->next;
	if (ret > 1)
	{
		maze->paths += (ret - 1);
		add_paths(maze->paths, &maze->route, maze->paths - (ret - 1), \
					LEN_MAX);
		fill_new_paths(maze, *row, maze->paths - (ret - 1), 0);
	}
	else if ((ret == 1 || ret == -1) && maze->been[ptr->v] != 1)
	{
		if (ret == -1)
			maze->route[*row][len] = 1;
		else if ((maze->been[ptr->v] = 1))
			maze->route[*row][len] = ptr->v;
	}
	else
		del_route(maze, *row);
}
