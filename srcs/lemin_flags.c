/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin_flags.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkarkaus <mkarkaus@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 22:16:17 by sreijola          #+#    #+#             */
/*   Updated: 2021/02/25 12:22:26 by mkarkaus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

int		print_options(int *flags)
{
	ft_printf("Options:\n-h: help\n-l: show amount of lines used\n");
	ft_printf("-q: quiet mode, only print moves\n-r: print routes\n");
	ft_printf("-s: print anthill stats\n");
	free(flags);
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
		while (++i <= routes[row][0])
			ft_printf("%s ", names[routes[row][i]]);
		ft_printf("\n");
	}
}

void	parse_flags(t_hill *ah)
{
	if (ah->flags[0] == 1)
		ft_printf("\nTurns used: %d\n\n", ah->best_turns);
	if (ah->flags[2] == 1)
		print_routes(ah->maze->best_set + 1, ah->maze->best_set[0][0], ah->name);
	if (ah->flags[3] == 1)
	{
		ft_printf("\nANTHILL:\nAnts: %d\n", ah->ants);
		ft_printf("Rooms: %d\nLinks: %d\n\n", ah->rooms, ah->links);
	}
}

void	which_flags(char c, int **flags)
{
	(*flags)[4] = 1;
	if (c == 'l')
		(*flags)[0] = 1;
	if (c == 'q')
		(*flags)[1] = 1;
	if (c == 'r')
		(*flags)[2] = 1;
	if (c == 's')
		(*flags)[3] = 1;
}

int		save_flags(char **av, t_hill *ah)
{
	int	row;
	int	i;

	row = 0;
	ah->flags = (int *)ft_memalloc(sizeof(int) * 5);
	while (av[++row])
	{
		i = 0;
		while (av[row][++i])
		{
			if (av[row][0] == '-' && ft_strchr("hlqrs", av[row][i]))
			{
				if (av[row][i] == 'h')
					return (print_options(ah->flags));
				which_flags(av[row][i], &ah->flags);
			}
			else
				return (print_options(ah->flags));
		}
	}
	return (1);
}
