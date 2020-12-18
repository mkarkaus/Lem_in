/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pr_intarr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkarkaus <mkarkaus@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/02 11:34:06 by mkarkaus          #+#    #+#             */
/*   Updated: 2020/12/15 13:19:30 by mkarkaus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

void	ft_pr_intarr(int **arr, int maxr, int maxc, int fd)
{
	int		i;
	int		j;

	i = -1;
	while (++i < maxr)
	{
		j = 0;
		while (j < maxc)
		{
			ft_printf("{fd}%i ", fd, arr[i][j]);
			j++;
		}
		ft_printf("{fd}\n", fd);
	}
}
