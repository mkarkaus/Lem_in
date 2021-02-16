/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin_print.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sreijola <sreijola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/06 12:38:29 by sreijola          #+#    #+#             */
/*   Updated: 2021/02/16 14:04:07 by sreijola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

int		use_path(int path, int **set, int ant, int max_ants)
{
	int		row;
	int		len_sum;

	len_sum = 0;
	row = 0;
	while (++row != path)
		len_sum += set[path][0] - set[row][0];
	if (max_ants - ant > len_sum - 1)
		return (1);
	return (0);
}

void	apply_path(t_hill *ah, int *path, int ant, int start_turn)
{
	char	*move;
	int		i;

	i = 1;
	while (i <= path[0])
	{
		move = ft_strjoin(ft_strjoin(" L", ft_itoa(ant), 2), \
				ft_strjoin("-", ah->name[path[i]], 0), 3);
		ft_lstadd(&ah->moves[start_turn + i - 1], ft_lstnew(move, ft_strlen(move)));
		free(move);
		i++;
	}
}

void	init_moves(t_hill *ah)
{
	int		i;

	i = 0;
	ah->moves = (t_list **)ft_memalloc(sizeof(t_list *) * ah->best_turns);
	while (i < ah->best_turns)
	{
		ah->moves[i] = NULL;
		i++;
	}
}

void	save_moves(t_hill *ah)
{
	int		cur_turn;
	int		ant;
	int		path;

	ant = 1;
	cur_turn = 0;
	path = 1;
	init_moves(ah);
	while (ant <= ah->ants)
	{
		if (path <= ah->best_set[0][0] && \
			use_path(path, ah->best_set, ant, ah->ants))
		{
			apply_path(ah, ah->best_set[path], ant, cur_turn);
			path++;
			ant++;
		}
		else
		{
			cur_turn++;
			path = 1;
		}
	}
}

void	print_moves(t_hill *ah)
{
	int		i;
	
	i = -1;
	save_moves(ah);
	while (++i < ah->best_turns && ah->moves[i])
	{
		ft_printf("%s", ah->moves[i]->content + 1);
		ah->moves[i] = ah->moves[i]->next;
		while (ah->moves[i] != NULL)
		{
			ft_printf("%s", ah->moves[i]->content);
			ah->moves[i] = ah->moves[i]->next;
		}
		write(1, "\n", 1);
	}
}
