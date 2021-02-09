/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin_flags.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sreijola <sreijola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 22:16:17 by sreijola          #+#    #+#             */
/*   Updated: 2021/02/09 11:41:35 by sreijola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

int		print_options(void)
{
	ft_printf("Options:\n-h: help\n-l: show amount of lines used\n");
	ft_printf("-q: quiet mode, only print moves\n-r: print routes\n");
	ft_printf("-s: print anthill stats\n");
	return (0);
}

void	print_routes(int **routes, int paths, char **names)
{
	int i;
	int row;

	row = -1;
	while (++row < paths)
	{
		i = 0;
		ft_printf("Route %d: ", row);
		while (++i < routes[row][0])
			ft_printf("%s ", names[routes[row][i]]);
		ft_printf("\n");
	}
}

void	print_stats(int rms, int lnks, int a)
{
	ft_printf("\nANTHILL:\nAnts: %d\nRooms: %d\nLinks: %d\n\n", a, rms, lnks);
}

void	parse_flags(t_hill *ah)
{
	if (ah->flags[0] == 1)
		ft_printf("\nLines/turns needed: %d\n\n", ah->best_turns - 1);
	// if (ah->flags[2] == 1)
	// 	print_routes(ah->maze->best_set, ah->maze->best_paths, ah->name);
	if (ah->flags[3] == 1)
		print_stats(ah->rooms, ah->links, ah->ants);
}

int		save_flags(int c, char **av, t_hill *ah)
{
	int	row;
	int	i;

	row = 0;
	ah->flags = (int *)ft_memalloc(sizeof(int) * 4);
	while (av[++row])
	{
		i = 0;
		while (av[row][++i])
		{
			if (av[row][0] == '-' && ft_strchr("hlqrs", av[row][i]))
			{
				ah->flags[4] = 1;
				if (av[row][i] == 'h')
					return (print_options());
				ah->flags[0] = (av[row][i] == 'l') ? 1 : 0;
				ah->flags[1] = (av[row][i] == 'q') ? 1 : 0;
				ah->flags[2] = (av[row][i] == 'r') ? 1 : 0;
				ah->flags[3] = (av[row][i] == 's') ? 1 : 0;
			}
			else
				return (print_options());
		}
	}
	return (1);
}
