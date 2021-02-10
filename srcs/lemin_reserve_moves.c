/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin_reserve_moves.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sreijola <sreijola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 10:45:15 by sreijola          #+#    #+#             */
/*   Updated: 2021/02/10 13:48:15 by sreijola         ###   ########.fr       */
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

int		path_clear(int **res, t_graph *maze, int path, int turns)
{
	int		i;

	i = 0;
	while (i + 1 < maze->max_level && i < turns && maze->route[path][i + 1] != 1)
	{
		if (res[i][maze->route[path][i + 1]] != 0)
			return (0);
		i++;
	}
	return (1);
}

void	set_ants_on_paths(int ***res, t_hill *ah, int cur, int *turns)
{
	int		sum_i;
	int		turn;
	int		len_sum;
	int		route_i;

	turn = 1;
	route_i = -1;
	while (cur <= ah->ants)
	{
		route_i = 0;
		while (route_i < ah->maze->paths && cur <= ah->ants)
		{
			len_sum = 0;
			sum_i = -1;
			while (++sum_i != route_i)
				len_sum += ah->maze->route[route_i][0] - ah->maze->route[sum_i][0];
			if (ah->ants - cur > len_sum - 1 && path_clear(*res + turn, ah->maze, route_i, *turns - turn))
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
	int		set;

	set = -1;
	ah->best_turns = INT_MAX;
	ah->start_i = -1;
	while (++set < ah->maze->max_sets && ah->maze->sets[set][0][0] != 0)
	{
		*res = NULL;
		*turns = 0;
		ah->maze->paths = ah->maze->sets[set][0][0];
		ah->maze->route = ah->maze->sets[set] + 1;
		move = (ah->maze->route[0][0] - ah->maze->sets[0][0][0] > 1) ? \
			ah->maze->sets[0][0][0] + (ah->maze->route[0][0] - ah->maze->sets[0][0][0]) :\
			ah->maze->sets[0][0][0] + 1;
		add_turns(move, ah->maze, res, *turns);
		*turns = move;
		set_ants_on_paths(res, ah, 1, turns);
		if (*turns < ah->best_turns)
		{
			if (ah->best_turns != INT_MAX)
				ft_tabarr_free(ah->best_res, ah->best_turns);
			ah->best_res = *res;
			ah->best_turns = *turns;
		}
		else
			ft_tabarr_free(*res, *turns);
	}
}
