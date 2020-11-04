/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin_routes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sreijola <sreijola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 10:45:15 by sreijola          #+#    #+#             */
/*   Updated: 2020/11/04 17:05:49 by sreijola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

void	add_turns(int turns, t_hill *ah, int ***res)
{
	int		**tmp;
	int		k;
	int		i;
	
	k = -1;
	tmp = ft_tabarr_malloc(turns, ah->rooms);
	if (*res != NULL)
	{
		while (++k < turns - 1)
			ft_memcpy(tmp[k], *res[k], sizeof(int) * ah->rooms);
		ft_tabarr_free(*res, turns - 1);
	}
	while (++k < turns)
	{
		i = -1;
		while(++i < ah->rooms)
			tmp[k][i] = (ah->maze->array[i].dd < 0) ? -1 : 0;
	}
	*res = tmp;
}

int		shortest_route(t_list *route, t_graph *maze, int ***res)
{
	t_node	*ptr;
	t_list	*tmp;
	int		moves;

	moves = 0;
	tmp = ft_lstnew(0, sizeof(int));
	route = tmp;
	while (tmp->content != 1)
	{
		etsi paras seuraava askel
		if (jos vapaana)
			tmp->next = ft_lstnew(maze->array[i]->head->v, sizeof(int));
		else (jos pysyy paikallaan)
			tmp->next = ft_lstnew(i, sizeof(int));
		tmp = tmp->next;
		moves++;
	}
	
	return (ft_lstlen(route));
}

void	save_routes(int ant, int *turns, int ***res, t_graph *maze)
{
	t_list	*route;
	int		moves;
	int		k;
	int		i;
	
	k = -1;
	moves = shortest_route(&route, maze, &res);
	if (moves > *turns)
	{
		add_turns(moves, ah, &res);
		*turns = moves;
	}
	while (route != NULL)
	{
		res[++k][route->content] = ant;
		route = route->next;
	}
}


int		route_ants(t_hill *ah)
{
	int		**res;
	int		ant;
	int		turns;

	ant = 0;
	res = NULL;
	turns = 0;
	while(++ant < ah->ants)
		save_routes(ant, &turns, &res, ah->maze);
	ft_pr_intarr(res, turns, ah->rooms, 1);
}
