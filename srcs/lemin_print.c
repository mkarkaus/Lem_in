/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin_print.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sreijola <sreijola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/06 12:38:29 by sreijola          #+#    #+#             */
/*   Updated: 2021/02/10 12:27:18 by sreijola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

int		find_ant_move(int ant, int **res, int turn, int rooms)
{
	int		rm;
	int		nxt_rm;

	rm = 2;
	nxt_rm = 2;
	while (rm < rooms && res[turn][rm] != ant)
		rm++;
	while (nxt_rm < rooms && res[turn + 1][nxt_rm] != ant)
		nxt_rm++;
	if ((nxt_rm == rm && nxt_rm != rooms && rm != rooms))
		return (0);
	else if ((nxt_rm == rm && nxt_rm == rooms \
			&& !sneaky_ant(res, turn, turn + 2, rooms)))
		return (-1);
	else if (nxt_rm == rooms && rm != rooms)
		return (1);
	else if ((nxt_rm == rm && nxt_rm == rooms \
			&& sneaky_ant(res, turn, turn + 2, rooms)))
		return (0);
	return (nxt_rm);
}


void	print_content(t_hill *ah, int **in_end, int i, int sneaky)
{
	int first;
	int ant;
	int	rm;
	
	first = 1;
	ant = 0;
	while (++ant <= ah->ants)
		if ((*in_end)[ant - 1] == 0 \
			&& ((rm = find_ant_move(ant, ah->best_res, i, ah->rooms)) > 0 \
			|| (rm == -1 && sneaky == 0)))
		{
			if (rm == -1 && (sneaky = 1))
				rm = 1;
			if (first == 0)
				write(1, " ", 1);
			if ((*in_end)[ant - 1] != 1)
			{
				if (rm == 1)
					(*in_end)[ant - 1] = 1;
				ft_printf("L%d-%s", ant, ah->name[rm]);
				first = 0;
			}
		}
}

void	print_moves(t_hill *ah)
{
	int		i;
	int		*in_end;

	in_end = (int *)ft_memalloc(ah->ants * sizeof(int));
	i = 0;
	while (i + 1 < ah->best_turns)
	{
		print_content(ah, &in_end, i, 0);
		i++;
		write(1, "\n", 1);
	}
	free(in_end);
}
