/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkarkaus <mkarkaus@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/21 12:15:12 by mkarkaus          #+#    #+#             */
/*   Updated: 2021/03/05 10:12:24 by mkarkaus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

void	free_struct_elements(t_hill *ah, int error)
{
	(error <= -2) ? ft_lstfree(ah->input) : 0;
	(error <= -2) ? ft_lstfree(ah->data) : 0;
	(error <= -3) ? ft_strarr_free(ah->name) : 0;
	(error <= -4 && ah->links > 0) ? ft_tabarr_free(ah->link, ah->links) : 0;
	if (error == -5)
	{
		ft_tabarr_free(ah->maze->route, ah->maze->paths);
		free(ah->maze->flow);
		free(ah->maze->been);
		ft_tabarr_free(ah->maze->set, ah->maze->set[0][0] + 1);
	}
	if (error <= -5)
	{
		ft_tabarr_free(ah->maze->used, SEARCH_TIMES + 1);
		ft_tabarr_free(ah->maze->best_set, ah->maze->best_set[0][0] + 1);
		ft_graph_free(ah->maze);
	}
	free(ah->flags);
}

int		handle_errors(t_hill *ah, int error)
{
	if (error == -1)
		ft_printf("{fd}ERROR: Empty map!\n", 2);
	else if (error == -2)
		ft_printf("{fd}ERROR: Invalid input!\n", 2);
	else if (error == -3)
		ft_printf("{fd}ERROR: Rooms are invalid!\n", 2);
	else if (error == -4)
		ft_printf("{fd}ERROR: Invalid link!\n", 2);
	else if (error == -5)
		ft_printf("{fd}ERROR: No valid routes to the end of the maze!\n", 2);
	free_struct_elements(ah, error);
	return (error);
}

int		main(int ac, char **av)
{
	t_hill	ah;
	int		ret;

	ah.input = NULL;
	if (save_flags(av, &ah) == 0)
		return (0);
	if ((ret = get_data(&ah, &ah.input)) < 0)
		return (handle_errors(&ah, ret));
	if ((ret = find_route_sets(ah.maze, ah.ants)) < 0)
		return (handle_errors(&ah, ret));
	if (ah.flags[1] != 1)
	{
		ft_lstprint(ah.input);
		write(1, "\n", 1);
	}
	print_moves(&ah);
	if (ac > 1 && ah.flags[4] == 1)
		parse_flags(&ah);
	free_struct_elements(&ah, -6);
	return (0);
}
