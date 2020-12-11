/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin_graph_maze.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkarkaus <mkarkaus@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/06 13:28:46 by mkarkaus          #+#    #+#             */
/*   Updated: 2020/12/11 11:41:38 by mkarkaus         ###   ########.fr       */
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

/*
**	Function(graph, room where we came from) which traverses vertices until start room comes across or all the linked rooms
**	are already in "been-in" queue (which means we have reached deadend which doesn't have route to start without going back to
**	"room where we came from").
**
**	If it turns out that it's deadend, then we iterate through the "been-in" list and set their 'dd' to -2.
**
**	Remember to change all conditions using (dd != -1) to (dd >= 0)
*/

// int		check_deadend(t_hill *ah, int room)
// {
// 	int			*queue;
// 	int			*been;
// 	int			*temp;
// 	t_node		*node;

// 	int			i;
// 	int			k;

// 	k = -1;
// 	i = -1;
// 	queue = (int *)ft_memalloc(ah->rooms * sizeof(int));//     queue of 'to-be-checked' rooms
// 	been = (int *)ft_memalloc(ah->rooms * sizeof(int));//      queue of rooms we have checked in this branch
// 	temp = (int *)ft_memalloc(ah->rooms * sizeof(int));//      temporary container of rooms' dds
// 	// ft_printf("queue: %p     %d\n", queue, ah->rooms * sizeof(int));
// 	// ft_printf("been:  %p\n", been);
// 	// ft_printf("temp:  %p\n\n", temp);
// 	while (++i < ah->rooms)
// 	{
// 		queue[i] = -1;
// 		been[i] = -1;
// 		temp[i] = -1;
// 	}
// 	queue[0] = room;
// 	node = ah->maze->array[room].head;
// 	while (node->next && ah->maze->array[node->v].dd < 0 && room != 1 && node->v != 0)
// 	{
// 		// ft_printf(" wroom: [%d] node->v: [%d] \n", room, node->v);
// 		node = node->next;
// 		// ft_printf(" wroom: [%d] node->v: [%d] \n\n", room, node->v);
// 	}
// 	// ft_printf("OKAY\n");
// 	// ft_pr_intarr(&queue, 1, ah->rooms, 1);
// 	if (room != 1 && node->v != 0)
// 	{
// 		been[++k] = node->v;
// 		temp[k] = ah->maze->array[node->v].dd;
// 		ah->maze->array[node->v].dd = -3;
// 	}
// 	while (!ft_tabint_find(queue, 0, ah->rooms) && queue[0] != -1)
// 	{
// 		i = -1;
// 		while (queue[++i] != -1)
// 			if (!ft_tabint_find(been, queue[i], ah->rooms))
// 			{
// 				been[++k] = queue[i];
// 				temp[k] = ah->maze->array[been[k]].dd;
// 				ah->maze->array[been[k]].dd = -3;
// 			}
// 		remake_queue(ah->maze, &queue, 0, been);
// 	}
// 	i = -1;
// 	if (queue[0] == -1)
// 	{
// 		while (++i < ah->rooms && been[i] != -1)
// 		{
// 			if (temp[i] == -1)
// 				ah->maze->array[been[i]].dd = -2;
// 			else
// 				ah->maze->array[been[i]].dd = temp[i];
// 		}
// 	}
// 	else
// 		while (++i < ah->rooms && been[i] != -1)
// 			ah->maze->array[been[i]].dd = temp[i];
// 	free(queue);
// 	free(been);
// 	free(temp);
// 	return (queue[0] == -1);
// }

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
		{
			ah->maze->array[q[i]].dd = dis;
		}
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

void	requeue(t_graph **maze, int **queue, int only_clear, int *been)
{
	int			i;
	int			k;
	int			*temp;
	t_node		*node;
	t_alhead	*ptr;

	i = -1;
	temp = ft_memalloc((*maze)->ver * sizeof(int));
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
}

void	bfs_levels(t_graph **maze, char **name)
{
	int			*q;
	int			i;
	int			level;

	level = 0;
	i = -1;
	q = ft_memalloc((*maze)->ver * sizeof(int));
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
			(*maze)->array[q[i]].bfs_level = level;
		requeue(maze, &q, 0, NULL);
		level++;
	}
	free(q);
	(*maze)->array[1].bfs_level = INT_MAX;
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

void	pick_input()
{

}

void	handle_input_forks(t_graph **maze)
{
	int		level;
	int		i;
	int		found;

	level = 1;
	found = 1;
	while (found == 1)
	{
		found = 0;
		i = 0;
		while (++i < (*maze)->ver)// search for all rooms of bfs_level == level
		{
			if ((*maze)->array[i].bfs_level == level)
			{
				found = 1;
				if ((*maze)->array[i].in > 1)// search rooms with input forks
					pick_input();
			}
		}
		level++;
	}
}

int		graph_maze(t_hill *ah)
{
	int		i;

	i = -1;
	ah->maze = ft_graph_new(ah->rooms);
	while (++i < ah->links)
		ft_graph_edgeadd(ah->maze, ah->link[i][0], ah->link[i][1], 0);
	fill_distances(ah);
	bfs_levels(&ah->maze, ah->name);
	// ft_graph_print(ah->maze, ah->name);
	del_twoway(&ah->maze);
	del_zero_inputs(&ah->maze);// Not sure if works yet, check later
	// ft_graph_print(ah->maze, ah->name);
	del_zero_outputs(&ah->maze);
	handle_input_forks(&ah->maze);
	ft_graph_print(ah->maze, ah->name);
	if (ah->maze->array[0].dd == -1)
		return (-1);
	return (0);
}
