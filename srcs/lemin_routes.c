/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin_routes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkarkaus <mkarkaus@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 10:45:15 by sreijola          #+#    #+#             */
/*   Updated: 2021/01/11 12:32:27 by mkarkaus         ###   ########.fr       */
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
		while (++i < maze->ver)
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
				diff--;
			tmp[i] = 0;
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
			if (score >= maze->array[ptr->v].dd \
				&& maze->array[ptr->v].dd != -2 \
				&& ((move < turns && ((*res)[move][ptr->v] == 0 || ptr->v == 1)) || move >= turns) \
				&& been[ptr->v] != 1 \
				&& (ptr->v != 1 || sneaky_ant(*res, move - 1, turns, maze->ver)))
			{
				score = maze->array[ptr->v].dd;
				rm = ptr->v;
			}
			ptr = ptr->next;
		}
		been[rm] = 1;
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
		if (tmp == 1)
		{
			while (move < *turns)
			{
				(*res)[move][1]++;
				move++;
			}
		}
		else
			(*res)[move][tmp] = ant;
		move++;
		route = route->next;
	}
	ft_lstfree(free_route);
	return (0);
}

void	sort_routes(int ***route, int max_paths)
{
	int		row;
	int		swapped;
	int		*temp;

	swapped = 1;
	while (swapped == 1)
	{
		swapped = 0;
		row = 0;
		while (row + 1 < max_paths)
		{
			if ((*route)[row][0] > (*route)[row + 1][0])
			{
				temp = (*route)[row];
				(*route)[row] = (*route)[row + 1];
				(*route)[row + 1] = temp;
				swapped = 1;
			}
			row++;
		}
	}
}

void	route_lengths(int ***route, int max_paths, int **shrt)
{
	int		i;
	int		row;

	row = 0;
	while (row < max_paths)
	{
		i = 0;
		while ((*route)[row][i] != 1)
			i++;
		(*route)[row][0] = i;
		row++;
	}
	i = 0;
	while ((*shrt)[i] != 1)
		i++;
	(*shrt)[0] = i;
}

void	apply_route(int ***res, int *route, int start, int ant, int turns)
{
	int		i;

	i = 1;
	while (i <= route[0])
	{
		if (route[i] == 1)
		{
			while (start + i - 1 < turns)
			{
				(*res)[start + i - 1][1]++;
				i++;
			}
		}
		else
			(*res)[start + i - 1][route[i]] = ant;
		i++;
	}
}

void	first_ants(int ***res, int *shrt, int nbr_ants, int *turns)
{
	int		ant;

	ant = 1;
	while (ant <= nbr_ants)
	{
		apply_route(res, shrt, 0, 1, *turns);
		ant++;
	}
}

void	other_ants(int ***res, t_hill *ah, int cur, int *turns)
{
	int		sum_i;
	int		turn;
	int		len_sum;
	int		route_i;

	turn = 1;
	while (cur <= ah->ants)
	{
		route_i = 0;
		while (route_i < ah->maze->paths && cur <= ah->ants)
		{
			len_sum = 0;
			sum_i = -1;
			while (++sum_i != route_i)
				len_sum += ah->maze->route[route_i][0] - ah->maze->route[sum_i][0];
			if (ah->ants - cur > len_sum - 1 && ((*res)[turn][ah->maze->route[route_i][1]] == 0 ||
				ah->maze->route[route_i][1] == 1))
			{
				if (*turns < turn + ah->maze->route[route_i][0])
				{
					add_turns(turn + ah->maze->route[route_i][0], ah->maze, res, *turns);
					*turns = turn + ah->maze->route[route_i][0];
				}
				apply_route(res, ah->maze->route[route_i], turn, cur, *turns);
				cur++;
			}
			route_i++;
		}
		turn++;
	}	
}

void	reserve_moves(int ***res, t_hill *ah, int *turns)
{
	int		move;

	move = (ah->maze->route[0][0] - ah->maze->shrt[0] > 1) ? \
		ah->maze->shrt[0] + (ah->maze->route[0][0] - ah->maze->shrt[0]) :\
		ah->maze->shrt[0] + 1;
	if (move > *turns)
	{
		add_turns(move, ah->maze, res, *turns);
		*turns = move;
	}
	if (ah->maze->shrt[0] < ah->maze->route[0][0])
		first_ants(res, ah->maze->shrt, ah->maze->route[0][0] - \
				ah->maze->shrt[0], turns);
	other_ants(res, ah, ah->maze->route[0][0] - ah->maze->shrt[0] + 1, turns);
	// ft_pr_intarr(*res, *turns, ah->maze->ver, 1);
	// ft_pr_intarr(ah->maze->route, ah->maze->paths, ah->maze->max_level, 1);
}

int		lem_in(t_hill *ah)
{
	int		**res;
	// int		ant;
	int		turns;

	res = NULL;
	// ant = 0;
	turns = 0;
	route_lengths(&ah->maze->route, ah->maze->paths, &ah->maze->shrt);
	sort_routes(&ah->maze->route, ah->maze->paths);
	reserve_moves(&res, ah, &turns);
	// while(++ant <= ah->ants)
	// 	save_route(ant, &turns, &res, ah->maze);
	print_moves(res, turns, ah);
	ft_printf("turns: %d\n", turns - 1);
	// ft_tabarr_free(res, turns);
	return (0);
}
