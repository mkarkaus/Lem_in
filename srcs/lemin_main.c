/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sreijola <sreijola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/21 12:15:12 by mkarkaus          #+#    #+#             */
/*   Updated: 2021/02/18 15:49:04 by sreijola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

void	ft_grapher(t_graph *graph, int rm)
{
	t_node	*ptr;
	int		i;

	i = -1;
	while (++i < graph->ver)
	{
		if (i == rm || rm == -1)
		{
			ptr = graph->array[i].head;
			ft_printf("[ %d ] (dd:%d)", i, graph->array[i].dd);
			while (ptr != NULL)
			{
				ft_printf(" -> %d", ptr->v);
				ptr = ptr->next;
			}
			ft_printf("\n");
		}
	}
}

void	free_struct_elements(t_hill *ah, int error)
{
	int		i;
	int		temp;

	i = -1;
	(error <= -2) ? ft_lstfree(ah->input) : 0;
	(error <= -2) ? ft_lstfree(ah->data) : 0;
	(error <= -3) ? ft_strarr_free(ah->name) : 0;
	(error <= -3 && ah->rooms > 0) ? ft_tabarr_free(ah->coor, ah->rooms) : 0;
	(error <= -4 && ah->links > 0) ? ft_tabarr_free(ah->link, ah->links) : 0;
	if (error == -6)
	{
		ft_tabarr_free(ah->best_res, ah->best_turns);
		while (ah->maze->max_sets > 0 && ++i < SEARCH_TIMES)
		{
			temp = ah->maze->sets[i][0][0] + 1;
			while (--temp >= 0)
				free(ah->maze->sets[i][temp]);
			free(ah->maze->sets[i]);
		}
		free(ah->maze->sets);
	}
	if (error <= -5)
		ft_graph_free(ah->maze);
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
	int		**res;
	int		turns;

	turns = 0;
	ah.input = NULL;
	if (save_flags(av, &ah) == 0)
		return (0);
	if ((ret = get_data(&ah, &ah.input)) < 0)
		return (handle_errors(&ah, ret));
	(ah.flags[1] != 1) ? ft_lstprint(ah.input) : 0;
	write(1, "\n", 1);
	find_route_sets(ah.maze, ah.ants);
	reserve_moves(&res, &ah, &turns);
	print_moves(&ah);
	if (ac > 1 && ah.flags[4] == 1)
		parse_flags(&ah);
	free_struct_elements(&ah, -6);
	return (0);
}

	// clock_t begin = clock();
	// clock_t end = clock();
	// double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
	// ft_printf("{b_red}time_spent:%.2lf{r}\n", time_spent);