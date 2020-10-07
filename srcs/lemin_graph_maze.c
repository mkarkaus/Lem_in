/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graph_maze.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sreijola <sreijola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/06 13:28:46 by mkarkaus          #+#    #+#             */
/*   Updated: 2020/10/06 19:17:28 by sreijola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

void	graph_maze(t_hill *ah)
{
	int		i;

	i = -1;
	ah->maze = ft_graph_new(ah->rooms);
	while (++i < ah->links)
		ft_graph_edgeadd(ah->maze, ah->link[i][0], ah->link[i][1], 0);
}
