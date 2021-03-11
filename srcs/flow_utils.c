/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flow_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkarkaus <mkarkaus@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 16:17:59 by mkarkaus          #+#    #+#             */
/*   Updated: 2021/03/10 19:47:44 by mkarkaus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

void	fill_new_flow_paths(t_graph *maze, int fork, int k, int i, int len)
{
	t_node	*ptr;

	while (i < len && maze->route[fork][i + 1] != 0)
		i++;
	ptr = maze->array[maze->route[fork][i]].head;
	while (k < maze->paths && ptr)
	{
		if (maze->res[ptr->v] == 0 && (ptr->flow == 2 || ptr->flow == -1))
		{
			if (maze->route[fork][i + 1] == 0)
				maze->route[fork][i + 1] = ptr->v;
			else
			{
				ft_memcpy(maze->route[k], maze->route[fork], \
					(len + 1) * sizeof(int));
				maze->route[k][i + 1] = ptr->v;
				maze->res[ptr->v] = 1;
				k++;
			}
		}
		ptr = ptr->next;
	}
}

int		count_new_flow_routes(t_graph *maze, int fork)
{
	t_node	*ptr;
	int		valid_routes;

	ptr = maze->array[fork].head;
	valid_routes = 0;
	while (ptr)
	{
		if (maze->res[ptr->v] != 1 && (ptr->flow == 2 || ptr->flow == -1))
		{
			if (ptr->v == 1)
				return (-1);
			valid_routes++;
		}
		ptr = ptr->next;
	}
	return (valid_routes);
}

int		add_to_flow_route(t_graph *maze, int prev_room, int *row, int len)
{
	int		ret;
	t_node	*ptr;

	ret = count_new_flow_routes(maze, prev_room);
	ptr = maze->array[prev_room].head;
	while (ptr && (maze->res[ptr->v] == 1\
		|| !(ptr->flow == 2 || ptr->flow == -1)))
		ptr = ptr->next;
	if (ret > 1)
	{
		maze->paths += (ret - 1);
		add_paths(maze->paths, &maze->route, maze->paths - (ret - 1), len);
		fill_new_flow_paths(maze, *row, maze->paths - (ret - 1), 0, len);
	}
	else if (ret == 1)
	{
		maze->res[ptr->v] = 1;
		maze->route[*row][len] = ptr->v;
	}
	else if ((ret == -1 && (maze->route[*row][len] = 1)) \
			|| (ret == 0 && maze->paths == 1 && len != 2))
		return (0);
	else
		del_route(maze, row);
	return (1);
}

void	apply_flow(t_graph *maze, int *path)
{
	t_node	*ptr;
	int		i;

	i = 0;
	while ((i + 1) < LEN_MAX && path[i + 1] != 0 && path[i] != 1 \
		&& !(path[i] == 0 && i != 0))
	{
		ptr = maze->array[path[i]].head;
		while (ptr->v != path[i + 1])
			ptr = ptr->next;
		if (ptr->flow == 2)
			ptr->flow = 1;
		else if (ptr->flow == -1)
			ptr->flow = 0;
		ptr = maze->array[path[i + 1]].head;
		while (ptr->v != path[i])
			ptr = ptr->next;
		if (ptr->flow == 2)
			ptr->flow = -1;
		else if (ptr->flow == 1)
			ptr->flow = 0;
		i++;
	}
}

void	search_flow(t_graph *maze)
{
	int			prev_room;
	int			len;
	int			i;

	len = 1;
	while (++len < LEN_MAX && maze->paths != 0)
	{
		i = -1;
		while (++i < maze->paths && maze->paths != 0)
			if (maze->route[i][len] == 0)
			{
				prev_room = maze->route[i][len - 1];
				if (maze->route[i][len - 1] == 1 \
					|| !add_to_flow_route(maze, prev_room, &i, len))
				{
					apply_flow(maze, maze->route[i]);
					maze->flow_set = 1;
					return ;
				}
			}
	}
}
