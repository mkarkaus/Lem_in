/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin_forks_in.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkarkaus <mkarkaus@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 14:36:48 by sreijola          #+#    #+#             */
/*   Updated: 2021/01/21 14:45:0 by mkarkaus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

void	del_route(t_graph *maze, int del)
{
	int		*temp;

	while (del < maze->paths - 1)// swaps the to-be-deleted path until it's the last
	{
		temp = maze->route[del];
		maze->route[del] = maze->route[del + 1];
		maze->route[del + 1] = temp;
		del++;
	}
	free(maze->route[del]);
	maze->paths--;
}

void	fill_new_paths(t_graph *maze, int fork, int *visited)
{
	t_node	*ptr;
	// t_node	*temp;
	int		i;
	int		k;

	k = 0;
	i = 0;
	while (maze->route[k][0] != -1)
		k++;
	while (i < maze->max_level && maze->route[fork][i + 1] != -1)
		i++;
	ptr = maze->array[maze->route[fork][i]].head;
	while (k < maze->paths && ptr)
	{
		if (!(maze->flow[maze->route[fork][i]] == 1 && maze->flow[ptr->v] == 1) && visited[ptr->v] == 0)
		{
			if (maze->route[fork][i + 1] == -1)
				maze->route[fork][i + 1] = ptr->v;
			else
			{
				ft_memcpy(maze->route[k], maze->route[fork], maze->max_level * sizeof(int));
				maze->route[k][i + 1] = ptr->v;
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
	*route = tmp;
}

int		count_new_routes(t_graph *maze, int fork, int *visited)
{
	t_node	*ptr;
	int		valid_routes;

	ptr = maze->array[fork].head;
	valid_routes = 0;
	while (ptr)
	{
		if (visited[ptr->v] == 0)
		{
			if (ptr->v == 1)
				return (-1);
			if (maze->been[ptr->v] != 1 && !(maze->flow[fork] == 1 && maze->flow[ptr->v] == 1))
				valid_routes++;
		}
		ptr = ptr->next;
	}
	return (valid_routes);
}

void	update_been(t_graph *maze, int keep)
{
	int		i;

	i = 1;
	while (maze->route[keep][i] != 1)
	{
		maze->been[maze->route[keep][i]] = 1;
		i++;
	}
}

void	rem_conflicting_paths(t_graph *maze, int *keep_row)
{
	int k;
	int	i;
	int row;

	k = 0;
	while (maze->route[*keep_row][++k] != -1)
	{
		row = 0;
		if (row == *keep_row)
			row++;
		while (row < maze->paths)
		{
			i = 1;
			while (i < maze->max_level && maze->route[row][i] != -1 && maze->route[row][i] != 1)
			{
				if (maze->route[row][i] == maze->route[*keep_row][k])
				{
					if (row < *keep_row)
						(*keep_row)--;
					del_route(maze, row);
					i = maze->max_level;
				}
				i++;
			}
			if (i != maze->max_level + 1)
				row++;
			if (row == *keep_row)
				row++;
		}
	}
	maze->route[*keep_row][k] = 1;
	update_been(maze, *keep_row);
}

void	fill_visited(t_graph *maze, int row, int **visited)
{
	int		i;
	
	i = -1;
	*visited = (int *)ft_memalloc(sizeof(int) * maze->ver);
	while (maze->route[row][++i] != -1)
		(*visited)[maze->route[row][i]] = 1;
}

void	add_to_route(t_graph *maze, int prev_room, int *row, int len)
{
	int		ret;
	t_node	*ptr;
	int		*visited;
	
	fill_visited(maze, *row, &visited);
	ret = count_new_routes(maze, prev_room, visited);
	ptr = maze->array[prev_room].head;
	while (ptr && (maze->been[ptr->v] == 1 || visited[ptr->v] == 1 || (maze->flow[prev_room] == 1 && maze->flow[ptr->v] == 1)))
		ptr = ptr->next;
	if (ret > 1)
	{
		maze->paths += (ret - 1);
		add_paths(maze->paths, &maze->route, maze->paths - (ret - 1), maze->max_level);
		// ft_printf("%d\n", maze->paths);
		fill_new_paths(maze, *row, visited);
	}
	else if ((ret == 1 || ret == -1) && maze->been[ptr->v] != 1 && visited[ptr->v] == 0)
	{
		if (ret == -1)
			rem_conflicting_paths(maze, row);
		else
			maze->route[*row][len] = ptr->v;
	}
	else
	{
		del_route(maze, *row);
		if (*row != 0)
			(*row)--; //not used *row--
	}
	free(visited);
}

void	create_set(t_graph *maze)
{
	int			prev_room;
	int			len;
	int			i;

	len = 1;
	while (++len < maze->max_level && maze->paths != 0)
	{
		i = -1;
		while (++i < maze->paths && maze->paths != 0)
		{
			if (maze->route[i][len] == -1)
			{
				prev_room = maze->route[i][len - 1];
				if (maze->route[i][len - 1] == 1)
					maze->route[i][len] = 1;
				else
					add_to_route(maze, prev_room, &i, len);
				i = -1;
			}
		}
		// if (len % 5 == 0)
		// 	ft_pr_intarr(maze->route, maze->paths, 120, 1);
		// write(1, "\n", 1);
	}
}
