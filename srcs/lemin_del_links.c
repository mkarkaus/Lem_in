/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin_del_links.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sreijola <sreijola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 15:20:03 by sreijola          #+#    #+#             */
/*   Updated: 2021/01/21 12:277:04 by sreijola         ###   ########.fr       */
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

void	del_twoway(t_graph *maze)
{
	int		i;
	t_node	*node;

	i = -1;
	while (++i < maze->ver)
	{
		node = maze->array[i].head;
		while (node != NULL)
		{
			if ((maze->array[i].bfs_level > maze->array[node->v].bfs_level) \
				|| (maze->array[i].bfs_level == maze->array[node->v].bfs_level && \
				maze->array[i].dd <= maze->array[node->v].dd))
				del_edge(&maze->array[i].head, &node);
			else
			{
				maze->array[i].out++;
				maze->array[node->v].in++;
				node = node->next;
			}
		}
	}
}

void	del_zero_inputs(t_graph *maze)
{
	t_node	*temp;
	int		changed;
	int		i;

	changed = 1;
	while (changed == 1 )
	{
		i = 1;
		changed = 0;
		while (++i < maze->ver && changed == 0)
		{
			if (maze->array[i].in == 0)
			{
				temp = maze->array[i].head;
				while (temp)
				{
					maze->array[temp->v].in--;
					del_edge(&maze->array[i].head, &temp);
				}
				maze->array[i].in = -1;
				maze->array[i].out = 0;
				changed = 1;
			}
		}
	}
}

void	del_zero_outputs(t_graph *maze)
{
	t_node	*temp;
	int		changed;
	int		i;

	changed = 1;
	while (changed == 1)
	{
		i = -1;
		changed = 0;
		while (++i < maze->ver && changed == 0)
		{
			if (i == 1 && i + 1 < maze->ver)
				i++;
			temp = maze->array[i].head;
			while (temp)
			{
				if (maze->array[temp->v].out == 0 && temp->v != 1)
				{
					maze->array[temp->v].in--;
					del_edge(&maze->array[i].head, &temp);
					maze->array[i].out--;
					changed = 1;
				}
				else
					temp = temp->next;
			}
		}
	}
}
