/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin_print.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkarkaus <mkarkaus@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/06 12:38:29 by sreijola          #+#    #+#             */
/*   Updated: 2020/12/03 11:56:53 by mkarkaus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

int		find_ant_move(int ant, int **res, int i, int rooms)
{
	int		rm;
	int		nxt_rm;

	rm = 1;
	nxt_rm = 2;
	while (nxt_rm < rooms && res[i + 1][nxt_rm] != ant)
		nxt_rm++;
	if (i == -1 && nxt_rm == rooms)
		rm = nxt_rm;
	else if (i > -1)
	{
		while (++rm < rooms && res[i][rm] != ant);
		// ft_printf("rm: [%d], ant [%d]\n", rm, ant);
		if (rm == rooms)
			return (1);
	}
	if (nxt_rm == rm) //ant = ei liiku, entäs suoraan startista endiin, 
		return (0);
	else if (nxt_rm == rooms) //ant on turnilla ja ei oo enää nextillä menee siis endiin: rm < rooms &&
		return (1);
	return (nxt_rm);
}

void	print_moves(int **res, int turns, t_hill *ah)
{
	int		i;
	int		ant;
	int		first;
	int		rm;
	int		*in_end;

	in_end = (int *)ft_memalloc(ah->ants * sizeof(int));
	i = -1;
	while (i + 1 < turns)
	{
		first = 1;
		ant = 0;
		while (++ant <= ah->ants)
		{
			// ft_printf("rm: [%d], ant [%d], i: [%d], turns: [%d]\n", rm, ant, i, turns);
			if ((rm = find_ant_move(ant, res, i, ah->rooms)) > 0)
			{
				if (first == 0)
					write(1, " ", 1);
				if (in_end[ant] != 1)
				{
					if (rm == 1)
						in_end[ant] = 1;
					ft_printf("L%d-%s", ant, ah->name[rm]);
					first = 0;
				}
			}
		}
		i++;
		write(1, "\n", 1);
	}
}
