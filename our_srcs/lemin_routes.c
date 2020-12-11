/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin_routes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkarkaus <mkarkaus@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 10:45:15 by sreijola          #+#    #+#             */
/*   Updated: 2020/12/07 11:59:05 by mkarkaus         ###   ########.fr       */
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
		{
			if (i == 1 && prev != 0)
				tmp[k][1] = tmp[k - 1][1];
			else
				tmp[k][i] = (maze->array[i].dd < 0) ? -1 : 0;
		}
		k++;
	}
	*res = tmp;
}

/*
**	sneaky ant means that ant goes straight from start room to end room and
**	therefore it's number is not present in reservation system.
*/

int		sneaky_ant(int **res, int move, int turns, int rooms)
{
	int		i;
	int		k;
	int		diff;
	int		ant;
	int		*tmp;

	if (move + 1 < turns && res[move][1] < res[move + 1][1])
	{
		tmp = (int *)ft_memalloc(sizeof(int) * rooms);
		ft_memcpy(tmp, res[move], sizeof(int) * rooms);
		diff = res[move + 1][1] - tmp[1];
		while (diff > 0)
		{
			i = 2;
			while (i < rooms && tmp[i] == 0)
				i++;
			if (i == rooms)
			{
				free(tmp);
				return (0);
			}
			ant = tmp[i];
			k = 2;
			while (k < rooms && res[move + 1][k] != ant)
				k++;
			if (k == rooms)
			{
				diff--;
			}
			tmp[i] = 0;
			// ft_printf("diff:[%d]  ant:[%d]  i:[%d]  k:[%d]\n", diff, ant, i, k);
			// ft_pr_intarr(&tmp, 1, rooms, 1);
			// write(1, "\n", 1);
			// ft_pr_intarr(&res[move + 1], 1, rooms, 1);
			// write(1, "\n", 1);
		}
		free(tmp);
	}
	return (1);
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
	move = 1;
	score = maze->array[0].dd;
	while (rm != 1)
	{
		ptr = maze->array[rm].head;
		while (ptr)
		{
			// ft_pr_intarr(*res, turns, maze->ver, 1);
			// write(1, "HASAMAJA\n", 9);
			// ft_printf("next[%d] move:[%d], turns:[%d]\n", ptr->v, move, turns);
			if (score >= maze->array[ptr->v].dd \
				&& maze->array[ptr->v].dd != -2 \
				&& ((move < turns && ((*res)[move][ptr->v] == 0 || ptr->v == 1)) || move >= turns) \
				&& been[ptr->v] != 1 \
				&& (ptr->v != 1 || sneaky_ant(*res, move - 1, turns, maze->ver)))
			{
				// ft_pr_intarr(*res, turns, maze->ver, 1);
				// write(1, "\n", 1);
				// ft_printf("[%d]\n", (*res)[move][ptr->v]);
				score = maze->array[ptr->v].dd;
				rm = ptr->v;
			}
			ptr = ptr->next;
		}
		been[rm] = 1;
		// ft_printf("room:[%d]\n", rm);
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
	// ft_lstprint(*route);
	tmp = (*route)->next;
	free((*route)->content);
	free(*route);
	*route = tmp;
}

int		save_route(int ant, int *turns, int ***res, t_graph *maze)
{
	t_list	*route;
	t_list	*free_route;
	int		move;
	int		tmp;

	find_route(&route, maze, res, *turns);
	free_route = route;
	move = ft_lstlen(route) + 1;
	if (move > *turns)
	{
		add_turns(move, maze, res, *turns);
		*turns = move;
	}
	move = 1;
	while (route)
	{
		tmp = *((int *)(route->content));
		// ft_printf("ant [%d] move:[%d] turns[%d] tmp[%d] ant in room:[%d]\n", ant, move, *turns, tmp, (*res)[move][tmp]);
		if (tmp == 1)
		{
			while (move < *turns)
			{
				// ft_printf("PLUS[%d]\n", (*res)[move][1]);
				(*res)[move][1]++;
				// ft_printf("PLUS[%d]\n", (*res)[move][1]);
				move++;
				// ft_printf("muuv[%d]\n", move);
			}
		}
		else
			(*res)[move][tmp] = ant;
		move++;
		route = route->next;
		// ft_pr_intarr(*res, *turns, maze->ver, 1);
		// write(1, "\n", 1);
	}
	ft_lstfree(free_route);
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
	ft_tabarr_free(res, turns);
	return (0);
}
