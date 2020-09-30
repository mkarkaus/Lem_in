/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sreijola <sreijola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/21 12:15:12 by mkarkaus          #+#    #+#             */
/*   Updated: 2020/09/30 21:57:07 by sreijola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

/*
**
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
**
**
**	- We'll search for all possible routes
**	- (and arrange them in order based on smallest cost (least moves))
**	- "linked tree(general tree?)" 
**	- how many moves away route is from "end"-room
**	- Ant moves through shortest AVAILABLE route
**
**
**
**
**
**
**
*/

void	init_struct(t_hill *ah)
{
	ah->ants = 0;
	ah->rooms = 0;
	ah->links = 0;
}

int		main()
{
	t_hill	ah;

	if (get_data(&ah) == -1)
		ft_printf("{fd}Invalid input!\n", 2);
	return (0);
}
