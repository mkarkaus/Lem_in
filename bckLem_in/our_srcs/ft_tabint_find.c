/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tabint_find.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkarkaus <mkarkaus@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/08 15:22:02 by mkarkaus          #+#    #+#             */
/*   Updated: 2020/10/08 15:25:03 by mkarkaus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

int		ft_tabint_find(int *tab, int to_find, int tab_len)
{
	int		i;

	i = -1;
	while (++i < tab_len)
	{
		if (tab[i] == to_find)
			return (1);
	}
	return (0);
}
