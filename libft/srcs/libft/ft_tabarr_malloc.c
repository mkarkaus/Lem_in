/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tabarr_malloc.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkarkaus <mkarkaus@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/28 04:11:06 by sreijola          #+#    #+#             */
/*   Updated: 2021/02/26 11:36:47 by mkarkaus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

int		**ft_tabarr_malloc(int max_rows, int max_cols)
{
	int		**tmp;
	int		i;

	i = -1;
	if (!(tmp = (int **)ft_memalloc((max_rows) * sizeof(int *))))
		return (NULL);
	while (++i < max_rows)
	{
		if (!(tmp[i] = (int *)ft_memalloc((max_cols) * sizeof(int))))
			return (NULL);
	}
	return (tmp);
}
