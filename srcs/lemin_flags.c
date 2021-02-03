/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin_flags.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sreijola <sreijola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 22:16:17 by sreijola          #+#    #+#             */
/*   Updated: 2021/02/03 22:37:32 by sreijola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

int		save_flags(int c, char **flags, t_hill *ah)
{
	int i;
	
	i = 0;
	ah->flags = 0;
	while (++i < c)
	{
		if (flags[i][0] == '-')
		{
			if (ft_strchr(flags[i], 'h'))
			{
				ft_printf("Options:\n-h: help\n-r: print routes\n");
				ft_printf("-l: show amount of lines used\n");
				ft_printf("-q: quiet mode, only print moves\n");
				ft_printf("-s: print anthill stats\n");
				return (0);
			}
			if (ft_strchr(flags[i], 'r'))
				ah->flags = 'r';
			if (ft_strchr(flags[i], 'l'))
				ah->flags = 'l';
			if (ft_strchr(flags[i], 'q'))
				ah->flags = 'q';
			if (ft_strchr(flags[i], 's'))
				ah->flags = 's';
		}
	}
}

void	print_routes(int **routes, char **names)
{
	int i;
	int row;
	
	row = 0;
	ft_printf("routes: %d\n", routes[0][0]);
	while (++row <= routes[0][0])
	{
		i = 0;
		ft_printf("Route %d: ", row);
		while (++i < routes[row][0])
			ft_printf("%s ", names[routes[row][i]]);
		ft_printf("\n");
	}
}

void	print_stats(int rms, int links, int ants)
{
	ft_printf("ANTHILL:\nAnts: %d\nRooms: %d\nLinks: %d\n", rms, links, ants);
}
