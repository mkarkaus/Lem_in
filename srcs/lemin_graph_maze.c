/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin_graph_maze.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkarkaus <mkarkaus@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/06 13:28:46 by mkarkaus          #+#    #+#             */
/*   Updated: 2021/01/06 18:06:34 by mkarkaus         ###   ########.fr       */
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

int		*find_shortest_route(t_graph *maze)
{
	t_node	*ptr;
	int		*shortest;
	int		room;
	int		i;

	// ft_printf("max_level:%d\n", maze->max_level);
	shortest = (int *)ft_memalloc(maze->max_level * sizeof(int));
	// ft_printf("maze->max_level:%d\n", maze->max_level);
	i = 1;
	shortest[0] = 0;
	room = 0;
	while (room != 1)
	{
		ptr = maze->array[room].head;
		while (ptr)
		{
			if (maze->array[room].dd >= maze->array[ptr->v].dd)
				room = ptr->v;
			ptr = ptr->next;
		}
		shortest[i++] = room;
	}
	while (i < maze->max_level)
	{
		shortest[i] = room;
		i++;
	}	
	return (shortest);
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
	// ah->maze->shortest = find_shortest_route(ah->maze);
	free(q);
}

void	del_edge(t_node **head, t_node **del)
{
	t_node	*ptr;
	t_node	*temp;

	ptr = *head;
	temp = NULL;
	while (ptr != (*del))
	{
		temp = ptr;
		ptr = ptr->next;
	}
	if (temp == NULL)
	{
		*head = (*head)->next;
		free(*del);
		(*del) = *head;
	}
	else
	{
		temp->next = ptr->next;
		free(*del);
		(*del) = temp->next;
	}
}

void	requeue(t_graph **maze, int **queue, int only_clear, int *been)
{
	int			i;
	int			k;
	int			*temp;
	t_node		*node;
	t_alhead	*ptr;

	i = -1;
	// ft_printf("SAS\n");
	// ft_printf("vesiperä:%d\n", (*maze)->ver);
	temp = (int *)ft_memalloc((*maze)->ver * sizeof(int));
	// ft_printf("S=S\n");

	ft_memcpy(temp, *queue, (*maze)->ver * sizeof(int));
	while (++i < (*maze)->ver)
		(*queue)[i] = -1;
	i = 0;
	k = 0;
	ptr = (*maze)->array;
	if (only_clear == 0)
	{
		while (temp[k] != -1)
		{
			node = ptr[temp[k]].head;
			while (node != NULL)
			{
				if ((ptr[node->v].bfs_level == -1 && !ft_tabint_find(*queue, node->v, (*maze)->ver) && been == NULL) \
					|| (been != NULL && !ft_tabint_find(been, node->v, (*maze)->ver) && ptr[node->v].bfs_level != -3))
					(*queue)[i++] = node->v;
				node = node->next;
			}
			k++;
		}
	}
	free(temp);
	// temp = NULL;
}

void	bfs_levels(t_graph **maze)
{
	int			*q;
	int			i;
	int			level;

	level = 0;
	i = -1;
	q = (int *)ft_memalloc((*maze)->ver * sizeof(int));
	// ft_printf("(*maze)->ver:%d\n", (*maze)->ver);
	requeue(maze, &q, 1, NULL);
	q[0] = 0;
	while (++i < (*maze)->ver)
	{
		(*maze)->array[i].in = 0;
		(*maze)->array[i].out = 0;
		(*maze)->array[i].bfs_level = -1;
	}
	while (q[0] > -1)
	{
		i = -1;
		while (q[++i] != -1)
		{
			(*maze)->array[q[i]].bfs_level = level;
		
		}
		// ft_printf("i:%d   q[i]:%d\n", i, q[i]);
		requeue(maze, &q, 0, NULL);
		level++;
	}
	free(q);
	(*maze)->array[1].bfs_level = INT_MAX;
	(*maze)->max_level = level + 1;
}

void	del_twoway(t_graph **maze)
{
	int		i;
	t_node	*node;

	i = -1;
	while (++i < (*maze)->ver)
	{
		node = (*maze)->array[i].head;
		while (node != NULL)
		{
			if ((*maze)->array[i].bfs_level > (*maze)->array[node->v].bfs_level \
				|| ((*maze)->array[i].bfs_level == (*maze)->array[node->v].bfs_level && \
				(*maze)->array[i].dd <= (*maze)->array[node->v].dd))
				del_edge(&(*maze)->array[i].head, &node);
			else
			{
				(*maze)->array[i].out++;
				(*maze)->array[node->v].in++;
				node = node->next;
			}
		}
	}
}

void	del_zero_inputs(t_graph **maze)
{
	t_node	*temp;
	int		changed;
	int		i;

	changed = 1;
	while (changed == 1 )
	{
		i = 0;
		changed = 0;
		while (++i < (*maze)->ver && changed == 0)
		{
			if ((*maze)->array[i].in == 0)
			{
				temp = (*maze)->array[i].head;
				while (temp)
				{
					(*maze)->array[temp->v].in--;
					del_edge(&(*maze)->array[i].head, &temp);
				}
				(*maze)->array[i].in = -1;
				(*maze)->array[i].out = 0;
				changed = 1;
			}
		}
	}
}

void	del_zero_outputs(t_graph **maze)
{
	t_node	*temp;
	int		changed;
	int		i;

	changed = 1;
	while (changed == 1)
	{
		i = -1;
		changed = 0;
		while (++i < (*maze)->ver && changed == 0)
		{
			if (i == 1 && i + 1 < (*maze)->ver)
				i++;
			temp = (*maze)->array[i].head;
			while (temp)
			{
				if ((*maze)->array[temp->v].out == 0 && temp->v != 1)
				{
					(*maze)->array[temp->v].in--;
					del_edge(&(*maze)->array[i].head, &temp);
					(*maze)->array[i].out--;
					changed = 1;
				}
				else
					temp = temp->next;
			}
		}
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

void	update_links(t_graph **maze, int del)
{
	t_node	*ptr;
	int		row;
	int		found;
	int		k;
	int		i;

	i = (*maze)->max_level - 1;
	found = 0;
	while (((*maze)->route)[del][i] == -1 || ((*maze)->route)[del][i] == 1)
		i--;
	while (i >= 0)
	{
		row = 0;
		if (((*maze)->route)[del][i + 1] != -1)// maybe leaves one 'wrong' link if (*route)[*del][i + 1] == -1
		{
			while (row < (*maze)->paths - 1 && found == 0)
			{
				k = 0;
				while (k < (*maze)->max_level - 1 && found == 0)
				{
					if (((*maze)->route)[row][k] == ((*maze)->route)[del][i] \
						&& ((*maze)->route)[row][k + 1] == ((*maze)->route)[del][i + 1])
						found = 1;
					k++;
				}
				row++;
			}
			if (found == 0)
			{
				(*maze)->array[((*maze)->route)[del][i + 1]].in--;
				(*maze)->array[((*maze)->route)[del][i]].out--;
				ptr = (*maze)->array[((*maze)->route)[del][i]].head;
				while (ptr->next && ptr->v != ((*maze)->route)[del][i + 1])
					ptr = ptr->next;
				del_edge(&(*maze)->array[((*maze)->route)[del][i]].head, &ptr);
			}
		}
		i--;
	}
}

void	del_route(t_graph **maze, int *del)
{
	int		*temp;
	int		found;
	int		rm;
	int		i;
	int		k;

	rm = 1;// starts from bfs_level 2 room
	k = 0;
	// ft_printf("del:%d\n", *del);
	while (((*maze)->route)[*del][++rm] != -1 && ((*maze)->route)[*del][rm] != 1)
	{
		k = 0;
		found = 0;
		while (found != 1 && (k < (*maze)->paths && (k != *del || (++k && k < (*maze)->paths))))
		{
			i = 1;
			while (++i < (*maze)->max_level)
				if (((*maze)->route)[k][i] == ((*maze)->route)[*del][rm])
					found = 1;
			k++;
		}
		if (found != 1)
			(*maze)->been[((*maze)->route)[*del][rm]] = 0;
	}
	i = 0;
	while (*del + i < (*maze)->paths - 1)// swaps the to-be-deleted path until it's the last
	{
		temp = ((*maze)->route)[*del + i];
		((*maze)->route)[*del + i] = ((*maze)->route)[*del + i + 1];
		((*maze)->route)[*del + i + 1] = temp;
		i++;
	}
	// ft_pr_intarr((*maze)->route, (*maze)->paths, (*maze)->max_level, 1);
	update_links(maze, *del + i);
	free(((*maze)->route)[*del + i]);
	(*maze)->paths--;
}

void	pick_route(t_graph **maze, int *path, int infork)
{
	int		i;
	int		k;
	int		m;
	int		k_out_forks;
	int		path_out_forks;

	// i = -1;
	k = 0;
	path_out_forks = 0;
	k_out_forks = 0;
	while (1)
	{
		m = -1;
		if (k == *path)
			k++;
		while (++m < (*maze)->max_level)
		{
			ft_printf("1\n");
			ft_pr_intarr((*maze)->route, (*maze)->paths, (*maze)->max_level, 1);
			ft_printf("infork:%d, path:%d, k:%d, m:%d\n", infork, *path, k, m);
			if (((*maze)->route)[k][m] == infork)
			{
				ft_printf("3\n");
				m = 0;
				i = 0;
				while (((*maze)->route)[*path][++i] != infork)// laskee output-forkkien määrän annetulta (*path) reitiltä
				{
					// ft_printf("infork:%d, path:%d, i:%d, k:%d, %d\n", infork, *path, i, k, ((*maze)->route)[*path][i]);
					if ((*maze)->array[((*maze)->route)[*path][i]].out > 1)
						path_out_forks++;
				}
				while (((*maze)->route)[k][++m] != infork)// laskee output-forkkien määrän k-reitiltä
					if ((*maze)->array[((*maze)->route)[k][m]].out > 1)
						k_out_forks++;
				if ((path_out_forks > k_out_forks || \
					(k_out_forks == path_out_forks && i >= m)))
				{
					del_route(maze, path);
					(*path)--;
				}
				else
				{
					del_route(maze, &k);
					if (k < *path)
						(*path)--;
				}
				// ft_printf("\n\n");
				// ft_pr_intarr((*maze)->route, (*maze)->paths, (*maze)->max_level, 1);
				return ;
			}
			ft_printf("2\n");
		}
		k++;
	}
}

void	ft_grapher(t_graph *graph)
{
	t_node	*ptr;
	int		i;

	i = -1;
	while (++i < graph->ver)
	{
		ptr = graph->array[i].head;
		ft_printf("[ %d ] (dd:%d, level:%d, in:%d, out:%d)", i, graph->array[i].dd, graph->array[i].bfs_level, graph->array[i].in, graph->array[i].out);
		while (ptr != NULL)
		{
			ft_printf(" -> %d", ptr->v);
			ptr = ptr->next;
		}
		ft_printf("\n");
	}
}

void	fill_new_paths(t_graph **maze, int fork)
{
	t_node	*ptr;
	t_node	*temp;
	int		i;
	int		k;
	int		m;

	k = 0;
	i = 0;
	while (((*maze)->route)[k][0] != -1)
		k++;
	while (i < (*maze)->max_level && ((*maze)->route)[fork][i + 1] != -1)
		i++;
	ptr = (*maze)->array[((*maze)->route)[fork][i]].head;
	while (k < (*maze)->paths && ptr->next != NULL)
	{
		// ft_printf("((*maze)->route)[fork][i]:%d\n", ((*maze)->route)[fork][i]);
		m = i;
		ft_memcpy(((*maze)->route)[k], ((*maze)->route)[fork], (*maze)->max_level * sizeof(int));
		((*maze)->route)[k][i + 1] = ptr->v;
		while (m <= (*maze)->max_level && ptr->v == 1)
		{
			((*maze)->route)[k][m] = 1;
			m++;
		}
		// ft_printf("ptr->v:%d\n", ptr->v);
		if (((*maze)->been)[ptr->v] == 1)
		{
			temp = ptr->next;
			pick_route(maze, &k, ptr->v);
			ptr = temp;
			// ft_printf("ptr->v:%d, kukakuka:%d\n", ptr->v, ((*maze)->route)[fork][i]);
			// ft_printf("ollakko vai eiko olla\n");
		}
		else
		{
			k++;
			if (ptr->v != 1)
				((*maze)->been)[ptr->v] = 1;
			ptr = ptr->next;
		}
		// ft_grapher(*maze);
	}
	((*maze)->route)[fork][i + 1] = ptr->v;
	// ft_printf("2\n");
	if (((*maze)->been)[ptr->v] == 1)
	{
		temp = ptr->next;
		pick_route(maze, &k, ptr->v);
		ptr = temp;
	}
	// ft_printf("ONKO TAALA\n");
	if (ptr != NULL && ptr->v != 1)
		((*maze)->been)[ptr->v] = 1;
	// ft_grapher(*maze);
	// ft_pr_intarr((*maze)->route, (*maze)->paths, (*maze)->max_level, 1);
}

void	handle_input_forks(t_graph **maze)
{
	t_node		*ptr;
	int			prev_room;
	int			len;
	int			i;

	len = 1;
	while (++len <= (*maze)->max_level)
	{
		i = -1;
		while (++i < (*maze)->paths)
		{
			prev_room = ((*maze)->route)[i][len - 1];
			ptr = (*maze)->array[prev_room].head;
			if (((*maze)->route)[i][len] == -1 && (*maze)->array[prev_room].out > 1)
			{
				(*maze)->paths += ((*maze)->array[prev_room].out - 1);
				add_paths((*maze)->paths, &(*maze)->route, (*maze)->paths - ((*maze)->array[prev_room].out - 1), (*maze)->max_level);
				fill_new_paths(maze, i);
			}
			else if (((*maze)->route)[i][len - 1] == 1)
				((*maze)->route)[i][len] = 1;
			else if (((*maze)->route)[i][len] == -1)
			{
				((*maze)->route)[i][len] = ptr->v;
				if ((*maze)->been[ptr->v] == 1)
					pick_route(maze, &i, ptr->v);
				else if (ptr->v != 1)
					(*maze)->been[ptr->v] = 1;
			}
			ft_pr_intarr((*maze)->route, (*maze)->paths, (*maze)->max_level, 1);
			ft_grapher(*maze);
			ft_printf("\n\n");
		}
	}
	// ft_pr_intarr(*route, (*maze)->paths, (*maze)->max_level, 1);
}

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
				del_route(maze, &path);
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

void	create_routes(t_graph **maze)
{
	t_node		*ptr;
	// int			**route;
	int			len;
	int			i;

	(*maze)->route = ft_tabarr_malloc((*maze)->array[0].out, (*maze)->max_level + 1);
	(*maze)->been = (int *)ft_memalloc((*maze)->ver * sizeof(int));
	// (*maze)->paths = 0;
	ptr = (*maze)->array[0].head;
	i = 0;
	while (ptr)
	{
		len = -1;
		while (++len <= (*maze)->max_level)
			(*maze)->route[i][len] = -1;
		(*maze)->route[i][0] = 0;
		(*maze)->route[i][1] = ptr->v;
		ptr = ptr->next;
		i++;
	}
	(*maze)->paths = i;
	handle_input_forks(maze);
	// ft_grapher(*maze);
	handle_output_forks(maze);
	// ft_pr_intarr(route, (*maze)->paths, (*maze)->max_level, 1);
	// ft_printf("\n");
	// ft_tabarr_free(route, (*maze)->array[0].out);
}

int		graph_maze(t_hill *ah)
{
	int		i;

	i = -1;
	ah->maze = ft_graph_new(ah->rooms);
	while (++i < ah->links)
		ft_graph_edgeadd(ah->maze, ah->link[i][0], ah->link[i][1], 0);
	fill_distances(ah);
	bfs_levels(&ah->maze);
	del_twoway(&ah->maze);
	del_zero_inputs(&ah->maze);// Not sure if works yet, check later
	del_zero_outputs(&ah->maze);
	ah->maze->shortest = find_shortest_route(ah->maze);
	// ft_pr_intarr(&ah->maze->shortest, 1, ah->maze->max_level, 1);
	// ft_pr_intarr(&ah->maze->shortest, 1, ah->maze->max_level, 1);
	// ft_printf("\n");
	create_routes(&ah->maze);
	// ft_graph_print(ah->maze, ah->name);
	if (ah->maze->array[0].dd == -1)
		return (-1);
	return (0);
}
