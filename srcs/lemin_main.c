/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sreijola <sreijola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/21 12:15:12 by mkarkaus          #+#    #+#             */
/*   Updated: 2021/02/17 16:00:15 by sreijola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

/*
**						[0]
**						/  \
**					 [1]    [2]
**					  |	     |
**					  |     [3]
**					   \   /
**						[4]
**
**						.map - files STDOUT for my program:
**
**			4		<--- amount of ants
**			1 0 2	<--- creating a room called "1"
**			##start	<--- following room will be staring room:
**			0 2 0	<--- creating a room called "0" (starting room)
**			##end	<--- following room will be end room:
**			4 2 6	<--- creating a room called "4" (end room)
**			2 4 2	<--- creating a room called "2"
**			3 4 4	<--- creating a room called "3"
**			0-1		<--- new pipe from room "0" to room "1"
**			0-2		<--- new pipe from room "0" to room "2"
**			2-3		<--- new pipe from room "2" to room "3"
**			3-4		<--- new pipe from room "3" to room "4"
**			4-1		<--- new pipe from room "4" to room "1"
**
**						My programs standard output:
**
**			L1-1		<--- move ant "1" to room "1"
**			L1-4 L2-1	<--- move ant "1" to room "4" and ant "2" to room "1"
**			L2-4		<--- move ant "2" to room "4"
**
**	- v_anamy1.map endless loop (probably ant going backwards, shouldn't be able to do that) (DONE)
**	- case where ants go straight from start to end (route_ants print) (DONE)
**	- change algorithm to pick all the routes by comparing them to eachother and eliminating
**	  them until there's only routes with 0 bottlenecks.
**
*/

void	ft_grapher(t_graph *graph, int rm)
{
	t_node	*ptr;
	int		i;

	i = -1;
	while (++i < graph->ver)
	{
		if (i == rm || i == -1)
		{
			ptr = graph->array[i].head;
			ft_printf("[ %d ] (dd:%d, level:%d)", i, graph->array[i].dd, graph->array[i].bfs_level);
			while (ptr != NULL)
			{
				ft_printf(" -> %d", ptr->v);
				ptr = ptr->next;
			}
			ft_printf("\n");
		}
	}
}

void	free_struct_elements(t_hill *ah, int error, int ac)
{
	int		i;
	int		temp;

	i = 0;
	if (error <= -2)
	{
		ft_lstfree(ah->input);
		ft_lstfree(ah->data);
	}
	if (error <= -3)
		ft_strarr_free(ah->name);
	if (ah->rooms > 0 && error <= -3)
		ft_tabarr_free(ah->coor, ah->rooms);
	if (ah->links > 0 && error <= -4)
		ft_tabarr_free(ah->link, ah->links);
	if (ah->links > 0 && error <= -5)
		ft_graph_free(ah->maze);
	if (error < -5)
	{
		ft_tabarr_free(ah->best_res, ah->best_turns);
		while (ah->maze->max_sets > 0 && i < SEARCH_TIMES)
		{
			temp = ah->maze->sets[i][0][0] + 1;
			while (--temp >= 0)
				free(ah->maze->sets[i][temp]);
			free(ah->maze->sets[i]); //koska tallennetaan vain lyhin reitti ja sen määrä 0:teen
			i++;
		}
		free(ah->maze->sets);
	}
	if (ac > 1)
		free(ah->flags);
}

int		handle_errors(t_hill *ah, int error, int ac)
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
	free_struct_elements(ah, error, ac);
	return (error);
}

int		main(int ac, char **av)
{
	t_hill	ah;
	int 	ret;
	int		**res;
	int		turns;

	turns = 0;
	ah.input = NULL;
	if (ac > 1 && (save_flags(av, &ah) == 0))
		return (0);
	if ((ret = get_data(&ah, &ah.input)) < 0)
		return (handle_errors(&ah, ret, ac));
	(ac > 1 && ah.flags[1] != 1) ? ft_lstprint(ah.input) : 0;
	write(1, "\n", 1);
	find_route_sets(ah.maze, ah.ants);
	reserve_moves(&res, &ah, &turns);
	print_moves(&ah);
	if (ac > 1 && ah.flags[4] == 1)
		parse_flags(&ah);
	free_struct_elements(&ah, -6, ac);
	return (0);
}

	// clock_t begin = clock();
	// clock_t end = clock();
	// double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
	// ft_printf("{b_red}time_spent:%.2lf{r}\n", time_spent);