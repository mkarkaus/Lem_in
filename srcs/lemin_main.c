/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sreijola <sreijola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/21 12:15:12 by mkarkaus          #+#    #+#             */
/*   Updated: 2021/02/08 13:45:33 by sreijola         ###   ########.fr       */
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

void	free_struct_elements(t_hill *ah) //lista pitää vapauttaa get_datassa
{
	if (ah->name[0] != NULL)
		ft_strarr_free(ah->name);
	if (ah->rooms > 0)
		ft_tabarr_free(ah->coor, ah->rooms);
	if (ah->links > 0)
		ft_tabarr_free(ah->link, ah->links);
	if (ah->maze->array != NULL)
		ft_graph_free(ah->maze);
}

int		handle_errors(int error)
{
	if (error == -1)
		ft_printf("{fd}ERROR: Invalid input!\n", 2);
	else if (error == -2)
		ft_printf("{fd}ERROR: No links or invalid link!\n", 2);
	else if (error == -3)
		ft_printf("{fd}ERROR: No valid routes to the end of the maze!\n", 2);
	else if (error == -4)
		ft_printf("{fd}ERROR: Empty map!\n", 2);
	else if (error == -5)
		ft_printf("{fd}ERROR: Routing error!\n", 2);
	else if (error == -6)
		ft_printf("{fd}ERROR: Rooms are invalid!\n", 2);
	//free_struct_elements(&ah);
	return (error);
}

int		main(int ac, char **av)
{
	t_hill	ah;
	t_list	*input;
	int 	ret;

	input = NULL;
	if (ac > 1 && (save_flags(ac, av, &ah) == 0))
		return (0);
	if ((ret = get_data(&ah, &input)) < 0)
		return (handle_errors(ret));
	// ft_strarr_print(ah.name);
	// ft_pr_intarr(ah.coor, ah.rooms, 2, 1);
	// if (ah.flags[1] != 1)
	// ft_lstprint(input);
	// ft_printf("%d\n", ft_lstlen(input));
	write(1, "\n", 1);
	if ((ret = lem_in(&ah)) < 0) //remove error returns
		return (handle_errors(ret));
	if (ac > 1 && ah.flags[4] == 1)
		parse_flags(&ah);
	ft_lstfree(input);
	ft_printf("1\n");
	free_struct_elements(&ah);
	ft_printf("2\n");
	return (0);
}
