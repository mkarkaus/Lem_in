/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin_graph_maze.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkarkaus <mkarkaus@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/06 13:28:46 by mkarkaus          #+#    #+#             */
/*   Updated: 2020/12/07 15:31:18 by mkarkaus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

int		graph_maze(t_hill *ah)
{
	int		i;
	int		a;

	i = -1;
	ah->maze = ft_graph_new(ah->rooms);
	while (++i < ah->links)
		ft_graph_edgeadd(ah->maze, ah->link[i][0], ah->link[i][1], 0);
	i = -1;
	while (++i < ah->rooms)
	{
		ah->maze->array[i].antnb = (int *)ft_memalloc(sizeof(int) * ah->ants);
		a = -1;
		while (i == 0 && ++a < ah->ants)
			ah->maze->array[i].antnb[a] = 1;
		while (i != 0 && ++a < ah->ants)
			ah->maze->array[i].antnb[a] = 0;
		ah->maze->array[i].q = 0;
	}
	fill_distances(ah);
	i = -1;
	if (ah->maze->array[0].dd == -1)
		return (-1);
	return (0);
}

void	remake_queue(t_hill *ah, int **queue, int only_clear, int *been)
{
	int			i;
	int			k;
	int			*temp;
	t_node		*node;
	t_alhead	*ptr;

	i = -1;
	temp = ft_memalloc(ah->rooms * sizeof(int));
	ft_memcpy(temp, *queue, ah->rooms * sizeof(int));
	while (++i < ah->rooms)
		(*queue)[i] = -1;
	i = 0;
	k = 0;
	ptr = ah->maze->array;
	if (only_clear == 0)
	{
		while (temp[k] != -1)
		{
			node = ptr[temp[k]].head;
			while (node != NULL)
			{
				if ((ptr[node->v].dd == -1 && !ft_tabint_find(*queue, node->v, ah->rooms) && been == NULL) \
					|| (been != NULL && !ft_tabint_find(been, node->v, ah->rooms) && ptr[node->v].dd != -3))
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

int		check_deadend(t_hill *ah, int room)
{
	int			*queue;
	int			*been;
	int			*temp;
	t_node		*node;

	int			i;
	int			k;

	k = -1;
	i = -1;
	queue = (int *)ft_memalloc(ah->rooms * sizeof(int));//     queue of 'to-be-checked' rooms
	been = (int *)ft_memalloc(ah->rooms * sizeof(int));//      queue of rooms we have checked in this branch
	temp = (int *)ft_memalloc(ah->rooms * sizeof(int));//      temporary container of rooms' dds
	// ft_printf("queue: %p     %d\n", queue, ah->rooms * sizeof(int));
	// ft_printf("been:  %p\n", been);
	// ft_printf("temp:  %p\n\n", temp);
	while (++i < ah->rooms)
	{
		queue[i] = -1;
		been[i] = -1;
		temp[i] = -1;
	}
	queue[0] = room;
	node = ah->maze->array[room].head;
	while (node->next && ah->maze->array[node->v].dd < 0 && room != 1 && node->v != 0)
	{
		// ft_printf(" wroom: [%d] node->v: [%d] \n", room, node->v);
		node = node->next;
		// ft_printf(" wroom: [%d] node->v: [%d] \n\n", room, node->v);
	}
	// ft_printf("OKAY\n");
	// ft_pr_intarr(&queue, 1, ah->rooms, 1);
	if (room != 1 && node->v != 0)
	{
		been[++k] = node->v;
		temp[k] = ah->maze->array[node->v].dd;
		ah->maze->array[node->v].dd = -3;
	}
	while (!ft_tabint_find(queue, 0, ah->rooms) && queue[0] != -1)
	{
		i = -1;
		while (queue[++i] != -1)
			if (!ft_tabint_find(been, queue[i], ah->rooms))
			{
				been[++k] = queue[i];
				temp[k] = ah->maze->array[been[k]].dd;
				ah->maze->array[been[k]].dd = -3;
			}
		remake_queue(ah, &queue, 0, been);
	}
	i = -1;
	if (queue[0] == -1)
	{
		while (++i < ah->rooms && been[i] != -1)
		{
			if (temp[i] == -1)
				ah->maze->array[been[i]].dd = -2;
			else
				ah->maze->array[been[i]].dd = temp[i];
		}
	}
	else
		while (++i < ah->rooms && been[i] != -1)
			ah->maze->array[been[i]].dd = temp[i];
	// ft_printf("1\n");
	// ft_printf("2\n");
	free(queue);
	free(been);
	free(temp);
	return (queue[0] == -1);
}

void	fill_distances(t_hill *ah)
{
	int			*q;
	int			i;
	int			dis;

	dis = 0;
	i = -1;
	q = ft_memalloc(ah->rooms * sizeof(int));
	remake_queue(ah, &q, 1, NULL);
	q[0] = 1;
	while (++i < ah->rooms)
		ah->maze->array[i].dd = -1;
	while (q[0] > -1)
	{
		i = -1;
		while (q[++i] != -1)
		{
			if (check_deadend(ah, q[i]) == 0)
				ah->maze->array[q[i]].dd = dis;
			// ft_graph_print(ah->maze);
		}
		remake_queue(ah, &q, 0, NULL);
		dis++;
	}
	free(q);
}
