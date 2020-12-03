/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin_routes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkarkaus <mkarkaus@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 10:45:15 by sreijola          #+#    #+#             */
/*   Updated: 2020/12/03 11:02:30 by mkarkaus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

void	add_turns(int turns, t_graph *maze, int ***res, int prev)
{
	int		**tmp;
	int		k;
	int		i;
	
	k = 0;
	tmp = ft_tabarr_malloc(turns, maze->ver);
	if (*res != NULL)
	{
		while (k < prev)
		{
			ft_memcpy(tmp[k], (*res)[k], sizeof(int) * maze->ver);
			k++;
		}
		ft_tabarr_free(*res, prev);
	}
	while (k < turns)
	{
		i = -1;
		while(++i < maze->ver)
			tmp[k][i] = (maze->array[i].dd < 0) ? -1 : 0;
		k++;
	}
	*res = tmp;
}

void	next_steps(t_graph *maze, int ***res, t_list **route, int turns)
{
	int		score;
	t_node	*ptr;
	int		rm;
	int		move;
	int		*been;

	been = (int *)ft_memalloc(sizeof(int) * maze->ver);
	rm = 0;
	move = 0;
	score = maze->array[0].dd;
	while (rm != 1)
	{
		ptr = maze->array[rm].head;
		while (ptr)
		{
			if (score >= maze->array[ptr->v].dd && maze->array[ptr->v].dd != -2\
			&& ((move < turns && ((*res)[move][ptr->v] == 0 || ptr->v == 1))\
			|| move >= turns) && been[ptr->v] != 1)
			{
				score = maze->array[ptr->v].dd;
				rm = ptr->v;
				// ft_printf("rm: [%d]\n", ptr->v);
			}
			ptr = ptr->next;
		}
		been[rm] = 1;
		// ft_printf("[%d]\n", been[3]);
		(*route)->next = ft_lstnew(&rm, sizeof(int));
		*route = (*route)->next;
		move++;
	}
	free(been);
}

void	find_route(t_list **route, t_graph *maze, int ***res, int turns)
{
	t_list	*tmp;
	int		help;

	help = 0;
	tmp = ft_lstnew(&help, sizeof(int));
	*route = tmp;
	next_steps(maze, res, &tmp, turns);
	tmp = (*route)->next;
	free((*route)->content);
	free(*route);
	*route = tmp;
}

int		save_route(int ant, int *turns, int ***res, t_graph *maze)
{
	t_list	*route;
	int		move;
	int		tmp;
	
	find_route(&route, maze, res, *turns);
	move = ft_lstlen(route);
	if (move > *turns)
	{
		add_turns(move, maze, res, *turns);
		*turns = move;
	}
	move = 0;
	while (route)
	{
		tmp = *((int *)(route->content));
		//ft_printf("ant [%d] move:[%d] turns[%d] tmp [%d]\n", ant, move, *turns, tmp);
		if (tmp == 1)
		{
			while (move < *turns)
				(*res)[move++][1]++;
		}
		else
			(*res)[move][tmp] = ant;
		move++;
		route = route->next;
		// ft_pr_intarr(*res, *turns, maze->ver, 1);
	}
	return (0);
}

int		route_ants(t_hill *ah)
{
	int		**res;
	int		ant;
	int		turns;

	ant = 0;
	res = NULL;
	turns = 0;
	while(++ant <= ah->ants)
		save_route(ant, &turns, &res, ah->maze);
	print_moves(res, turns, ah);
	return (0);
}
