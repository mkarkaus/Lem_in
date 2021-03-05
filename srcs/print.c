/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkarkaus <mkarkaus@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/05 14:53:38 by mkarkaus          #+#    #+#             */
/*   Updated: 2021/03/05 15:07:41 by mkarkaus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

int		use_path(unsigned int path, unsigned int **set, unsigned int ant, \
			unsigned int max_ants)
{
	unsigned int	row;
	unsigned int	len_sum;

	len_sum = 0;
	row = 0;
	while (++row != path)
		len_sum += set[path][0] - set[row][0];
	if (len_sum == 0 || max_ants - ant > len_sum - 1)
		return (1);
	return (0);
}

void	apply_path(t_hill *ah, unsigned int *path, unsigned int ant, \
			int start_turn)
{
	t_list			*tmp;
	char			*move;
	unsigned int	i;

	i = 1;
	while (i <= path[0])
	{
		move = ft_strjoin(ft_strjoin(" L", ft_itoa(ant), 2), \
				ft_strjoin("-", ah->name[path[i]], 0), 3);
		tmp = ft_lstnew(move, ft_strlen(move) + 1);
		ft_lstadd(&ah->moves[start_turn + i - 1], tmp);
		free(move);
		i++;
	}
}

void	print_moves(t_hill *ah, unsigned int cur_turn)
{
	t_list	*tmp;

	write(1, ah->moves[cur_turn]->content + 1, \
		ft_strlen(ah->moves[cur_turn]->content) - 1);
	tmp = ah->moves[cur_turn]->next;
	free(ah->moves[cur_turn]->content);
	free(ah->moves[cur_turn]);
	ah->moves[cur_turn] = tmp;
	while (ah->moves[cur_turn] != NULL)
	{
		tmp = ah->moves[cur_turn]->next;
		write(1, ah->moves[cur_turn]->content, \
			ft_strlen(ah->moves[cur_turn]->content));
		free(ah->moves[cur_turn]->content);
		free(ah->moves[cur_turn]);
		ah->moves[cur_turn] = tmp;
	}
	write(1, "\n", 1);
}

void	create_moves(t_hill *ah)
{
	unsigned int	cur_turn;
	unsigned int	ant;
	unsigned int	path;

	ant = 1;
	cur_turn = 0;
	path = 1;
	ah->best_turns = ah->maze->best_set[0][1] + (ah->maze->best_set[0][2] > 0);
	ah->moves = (t_list **)ft_memalloc(sizeof(t_list *) * ah->best_turns);
	while (cur_turn < ah->best_turns)
	{
		if (ant <= ah->ants && path <= ah->maze->best_set[0][0] \
				&& use_path(path, ah->maze->best_set, ant, ah->ants))
			apply_path(ah, ah->maze->best_set[path++], ant++, cur_turn);
		else
		{
			if (ah->moves[cur_turn])
				print_moves(ah, cur_turn);
			cur_turn++;
			path = 1;
		}
	}
	free(ah->moves);
}
