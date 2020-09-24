/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkarkaus <mkarkaus@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/21 12:15:12 by mkarkaus          #+#    #+#             */
/*   Updated: 2020/09/24 12:41:07 by mkarkaus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/includes/libft.h"

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
*/

// void	create_rooms()
// {

// }

void	get_data()
{
	t_list	*data;
	t_list	*app;
	t_list	*start;
	char	*temp;
	int		ants;

	get_next_line(0, &temp, 0);
	ants = ft_atoi(temp);
	get_next_line(0, &temp, 0);
	data = ft_lstnew(temp, ft_strlen(temp) + 1);
	data->content = ft_strdup(temp);
	while (get_next_line(0, &temp, 0) > 0)
	{
		app = ft_lstnew(temp, ft_strlen(temp) + 1);
		app->content = ft_strdup(temp);
		if (!start)
			start = data;
		data->next = app;
		data = data->next;
	}
	ft_lstprint(start);
	// create_rooms();
}

int		main()
{
	get_data();
	return (0);
}
