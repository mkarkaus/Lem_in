/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin_graph_maze.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sreijola <sreijola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/06 13:28:46 by mkarkaus          #+#    #+#             */
/*   Updated: 2020/10/28 10:18:30 by sreijola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

void	graph_maze(t_hill *ah)
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
	}
	ah->maze->array[i].q = 0;
	fill_distances(ah);
}

void	remake_queue(t_hill *ah, int **queue, int only_clear)
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
				// ft_printf("[%d] [temp[k]: %d]\n", ptr[temp[k]].dd, temp[k]);
				// ft_printf("[%d] [temp[k]: %d]\n", ptr[temp[k]].head->v, temp[k]);
				if (ptr[node->v].dd == -1 && !ft_tabint_find(*queue, node->v, ah->rooms))
					(*queue)[i++] = node->v;
				node = node->next;
				// ft_printf("[%d], [%d], [%d], [%d], [%d]\n", (*queue)[0], (*queue)[1], (*queue)[2], (*queue)[3], (*queue)[4]);
				// i++;
			}
			k++;
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
	remake_queue(ah, &q, 1);
	q[0] = 1;
	while (++i < ah->rooms)
		ah->maze->array[i].dd = -1;
	while (q[0] > -1)
	{
		i = -1;
		while (q[++i] != -1)
			ah->maze->array[q[i]].dd = dis;
		remake_queue(ah, &q, 0);
		dis++;
	}
	free(q);
}
