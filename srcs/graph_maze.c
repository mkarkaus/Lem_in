/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graph_maze.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkarkaus <mkarkaus@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/06 13:28:46 by mkarkaus          #+#    #+#             */
/*   Updated: 2021/02/26 14:33:35 by mkarkaus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

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
	del_deadends(ah->maze);
	return (0);
}
