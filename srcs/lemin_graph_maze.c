/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin_graph_maze.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkarkaus <mkarkaus@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/06 13:28:46 by mkarkaus          #+#    #+#             */
/*   Updated: 2021/02/19 10:08:33 by mkarkaus         ###   ########.fr       */
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
	k = -1;
	ptr = maze->array;
	if (only_clear == 0)
		while (temp[++k] != -1)
		{
			node = ptr[temp[k]].head;
			while (node != NULL)
			{
				if ((ptr[node->v].dd == -1 && been == NULL) \
				&& !ft_tabint_find(*queue, node->v, maze->ver) \
				|| (been != NULL && ptr[node->v].dd != -3 \
				&& !ft_tabint_find(been, node->v, maze->ver)))
					(*queue)[i++] = node->v;
				node = node->next;
			}
		}
	free(temp);
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

void	del_deadends(t_graph *maze)
{
	t_node	*ptr;
	int		i;
	int		changed;

	changed = 1;
	while (changed == 1)
	{
		i = 2;
		changed = 0;
		while (changed == 0 && i < maze->ver)
		{
			if (maze->array[i].head && !maze->array[i].head->next)
			{
				ptr = maze->array[maze->array[i].head->v].head;
				while (ptr->v != i)
					ptr = ptr->next;
				del_edge(&maze->array[maze->array[i].head->v].head, &ptr);
				ptr = maze->array[i].head;
				del_edge(&maze->array[i].head, &ptr);
				changed = 1;
			}
			i++;
		}
	}
}

int		is_duplicate_link(t_node *lst, int rm)
{
	t_node	*ptr;

	ptr = lst;
	while (ptr)
	{
		if (rm == ptr->v)
			return (1);
		ptr = ptr->next;
	}
	return (0);
}

int		graph_maze(t_hill *ah)
{
	int		i;

	i = -1;
	ah->maze = ft_graph_new(ah->rooms);
	while (++i < ah->links)
		if (!is_duplicate_link(ah->maze->array[ah->link[i][0]].head, \
				ah->link[i][1]))
			ft_graph_edgeadd(ah->maze, ah->link[i][0], ah->link[i][1], 0);
	ah->maze->max_len = 200;
	fill_distances(ah);
	del_deadends(ah->maze);
	if (ah->maze->array[0].dd == -1)
		return (-1);
	return (0);
}
