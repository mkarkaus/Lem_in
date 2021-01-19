/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pr_chararr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkarkaus <mkarkaus@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/02 11:35:56 by mkarkaus          #+#    #+#             */
/*   Updated: 2020/09/02 11:36:08 by mkarkaus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

void	ft_pr_chararr(char **arr, int maxr, int fd)
{
	int		i;

	i = -1;
	while (++i < maxr)
		ft_printf("{fd}%s\n", fd, arr[i]);
}
