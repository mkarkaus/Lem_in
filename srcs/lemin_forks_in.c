/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin_forks_in.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sreijola <sreijola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 14:36:48 by sreijola          #+#    #+#             */
/*   Updated: 2021/01/18 18:33:14 by sreijola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"




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
				// ft_printf("187ver: %d, del link to room: %d\n", ((*maze)->route)[del][i], ptr->v);
				del_edge(&(*maze)->array[((*maze)->route)[del][i]].head, &ptr);
			}
			// ft_grapher(*maze);
		}
		i--;
	}
}

void	del_route(t_graph **maze, int del)
{
	int		*temp;
	int		found;
	int		rm;
	int		i;
	int		k;

	rm = 1;// starts from bfs_level 2 room
	k = 0;
	ft_printf("OLEN DEL_ROUTE del:%d\n", del);
	ft_pr_intarr((*maze)->route, (*maze)->paths, (*maze)->max_level, 1);
	while (((*maze)->route)[del][++rm] != -1 && ((*maze)->route)[del][rm] != 1)
	{
		k = 0;
		found = 0;
		while (found != 1 && (k < (*maze)->paths && (k != del || (++k && k < (*maze)->paths))))
		{
			i = 1;
			while (++i < (*maze)->max_level)
				if (((*maze)->route)[k][i] == ((*maze)->route)[del][rm])
					found = 1;
			k++;
		}
		if (found != 1)
			(*maze)->been[((*maze)->route)[del][rm]] = 0;
	}
	i = 0;
	while (del + i < (*maze)->paths - 1)// swaps the to-be-deleted path until it's the last
	{
		temp = ((*maze)->route)[del + i];
		((*maze)->route)[del + i] = ((*maze)->route)[del + i + 1];
		((*maze)->route)[del + i + 1] = temp;
		i++;
	}
	// ft_pr_intarr((*maze)->route, (*maze)->paths, (*maze)->max_level, 1);
	update_links(maze, del + i);
	ft_grapher(*maze);
	free(((*maze)->route)[del + i]);
	(*maze)->paths--;
}

int		del_other_routes(t_graph **maze, int rem, int infork, int index)
{
	int		i;
	int		deleted;
	int		found;
	int		path;

	path = 0;
	deleted = 0;
	while (path < (*maze)->paths && rem != 0)
	{
		i = 0;
		found = 0;
		while (i + 1 < (*maze)->max_level)
		{
			if ((*maze)->route[path][i] == rem && (*maze)->route[path][i + 1] != infork)
			{
				if (path < index)
					deleted = 1;
				del_route(maze, path);
				found = 1;
			}
			i++;
		}
		if (found == 0)
			path++;
	}
	return (deleted);
}

int		del_allbutone(t_graph **maze, int rem, int infork, int index)
{
	t_node	*ptr;
	int		i;

	i = 2;
	ptr = (*maze)->array[rem].head;
	while (ptr && rem != 0)
	{
		if (ptr->v == 1)
			infork = 1;
		ptr = ptr->next;
	}
	ft_printf("IN DEL ALL BUT ONE: rem:%d, infork:%d\n", rem, infork);
	while (i < (*maze)->ver && (*maze)->array[infork].in > 1 && infork != 1)
	{
		ft_printf("infork:%d, rem:%d, huone:%d\n", infork, rem, i);
		ptr = (*maze)->array[i].head;
		while (ptr)
		{
			ft_printf("huone josta lähtee:%d, linkki joka poistuu:%d\n", i, ptr->v);
			if (ptr->v == infork && i != rem)
			{
				(*maze)->array[infork].in--;
				(*maze)->array[i].out--;
				del_edge(&(*maze)->array[i].head, &ptr);
				ft_printf("tulin ulos deledgestä\n");
				ft_grapher(*maze);
			}
			else
				ptr = ptr->next;
		}
		i++;
	}
	// ptr = (*maze)->array[rem].head;
	// while (ptr)
	// {
	// 	if (ptr->v != infork)
	// 	{
	// 		(*maze)->array[infork].in--;
	// 		(*maze)->array[rem].out--;
	// 		ft_printf("123huone josta lähtee:%d, linkki joka poistuu:%d\n", rem, ptr->v);
	// 		del_edge(&(*maze)->array[rem].head, &ptr);
	// 	}
	// 	else
	// 		ptr = ptr->next;
	// }
	// ft_printf("rem:%d, infork:%d\n", rem, infork);
	// ft_pr_intarr((*maze)->route, (*maze)->paths, (*maze)->max_level, 1);
	// deleted = del_other_routes(maze, rem, infork);
	return (del_other_routes(maze, rem, infork, index));
}

int		pick_route(t_graph **maze, int *path, int infork, int index)
{
	int		i;
	int		k;
	int		m;
	int		ret;
	int		k_out_forks;
	int		path_out_forks;

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
			if (((*maze)->route)[k][m] == infork)// valitsee kahdesta reitistä paremman
			{
				m = 0;
				i = 0;
				// ft_pr_intarr((*maze)->route, (*maze)->paths, (*maze)->max_level, 1);
				// ft_printf("infork:%d, path:%d, k:%d, m:%d\n", infork, *path, k, m);
				while (((*maze)->route)[*path][++i] != infork)// laskee output-forkkien määrän annetulta (*path) reitiltä
					if ((*maze)->array[((*maze)->route)[*path][i]].out > 1)
						path_out_forks++;
				while (((*maze)->route)[k][++m] != infork)// laskee output-forkkien määrän k-reitiltä
					if ((*maze)->array[((*maze)->route)[k][m]].out > 1)
						k_out_forks++;
				if (path_out_forks > k_out_forks || \
					(k_out_forks == path_out_forks && i >= m))
				{
					// del_route(maze, *path);
					ret = del_allbutone(maze, (*maze)->route[k][m - 1], infork, index);
					// if (k < *path)
					// 	k--;
					ft_printf("k:%d, m:%d, infork:%d, *path:%d\n", k, m, infork, *path);
					// (*path)--;
				}
				else
				{
					// del_route(maze, k);
					ret = del_allbutone(maze, (*maze)->route[*path][i - 1], infork, index);
					if (k < *path)
						(*path)--;
				}
				*path -= ret;
				// ft_pr_intarr((*maze)->route, (*maze)->paths, (*maze)->max_level, 1);
				// ft_grapher(*maze);
				// ft_printf("\n\n");
				return (ret);
			}
				// ft_pr_intarr((*maze)->route, (*maze)->paths, (*maze)->max_level, 1);
		}
		k++;
	}
}

void	del_invalid_routes(t_graph **maze)
{
	int		i;

	i = 0;
	while (i < (*maze)->paths)
	{
		if ((*maze)->route[i][0] == -1)
			del_route(maze, i);
		else
			i++;
	}
}

void	fill_new_paths(t_graph **maze, int fork)
{
	t_node	*ptr;
	t_node	*temp;
	int		*change_check;
	int		i;
	int		k;
	int		m;

	k = 0;
	i = 0;
	ft_printf("ykkösfork:%d\n", fork);
	change_check = ft_memalloc((*maze)->max_level * sizeof(int));
	ft_memcpy(change_check, ((*maze)->route)[fork], (*maze)->max_level * sizeof(int));
	while (((*maze)->route)[k][0] != -1)
		k++;
	while (i < (*maze)->max_level && ((*maze)->route)[fork][i + 1] != -1)
		i++;
	ptr = (*maze)->array[((*maze)->route)[fork][i]].head;
	while (k < (*maze)->paths && ptr->next != NULL)
	{
		m = i;
		ft_memcpy(((*maze)->route)[k], ((*maze)->route)[fork], (*maze)->max_level * sizeof(int));
		((*maze)->route)[k][i + 1] = ptr->v;
		while (++m <= (*maze)->max_level && ptr->v == 1)
			((*maze)->route)[k][m] = 1;
		if (((*maze)->been)[ptr->v] == 1)
		{
			temp = ptr->next;
			// if (fork > k)
			// 	fork--;
			// ft_pr_intarr((*maze)->route, (*maze)->paths, (*maze)->max_level, 1);
			fork -= pick_route(maze, &k, ptr->v, fork);
			ft_printf("fork:%d\n", fork);
			// ft_pr_intarr((*maze)->route, (*maze)->paths, (*maze)->max_level, 1);
			ptr = temp;
			// k++;
		}
		else
		{
			k++;
			if (ptr->v != 1)
				((*maze)->been)[ptr->v] = 1;
			ptr = ptr->next;
		}
	}
	// if (!ft_tabnequ(change_check, ((*maze)->route)[fork], (*maze)->max_level))
	// {
	ft_printf("\n");
	// ft_pr_intarr(&((*maze)->route)[fork], 1, (*maze)->max_level, 1);
		// ft_pr_intarr((*maze)->route, (*maze)->paths, (*maze)->max_level, 1);
	// 	fork--;
	// }
	((*maze)->route)[fork][i + 1] = ptr->v;
	if (((*maze)->been)[ptr->v] == 1)
	{
		temp = ptr->next;
		pick_route(maze, &k, ptr->v, 0);
		ptr = temp;
	}
	if (ptr != NULL && ptr->v != 1)
		((*maze)->been)[ptr->v] = 1;
	free(change_check);
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
		while (++i < (*maze)->paths && (*maze)->route[i][0] != -1)
		{
			if (((*maze)->route)[i][len] == -1)
			{
				prev_room = ((*maze)->route)[i][len - 1];
				ft_printf("prev:%d\n", prev_room);
				ptr = (*maze)->array[prev_room].head;
				ft_grapher(*maze);
				if (((*maze)->route)[i][len] == -1 && (*maze)->array[prev_room].out > 1)
				{
					ft_printf("outfork löydetty: prev_room:%d, out:%d\n", prev_room, (*maze)->array[prev_room].out);
					(*maze)->paths += ((*maze)->array[prev_room].out - 1);
					add_paths((*maze)->paths, &(*maze)->route, (*maze)->paths - ((*maze)->array[prev_room].out - 1), (*maze)->max_level);
					fill_new_paths(maze, i);
					del_invalid_routes(maze);
					ft_pr_intarr((*maze)->route, (*maze)->paths, (*maze)->max_level, 1);
				}
				else if (((*maze)->route)[i][len - 1] == 1)
					((*maze)->route)[i][len] = 1;
				else if (((*maze)->route)[i][len] == -1)
				{
					((*maze)->route)[i][len] = ptr->v;
					if ((*maze)->been[ptr->v] == 1)
					{
						pick_route(maze, &i, ptr->v, 0);
						ft_pr_intarr((*maze)->route, (*maze)->paths, (*maze)->max_level, 1);
					}
					else if (ptr->v != 1)
						(*maze)->been[ptr->v] = 1;
				}
				i = -1;
			}
			// ft_grapher(*maze);
		}
		ft_printf("\n\n");
	}
}
