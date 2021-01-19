/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tabarr_malloc.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkarkaus <mkarkaus@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/28 04:11:06 by sreijola          #+#    #+#             */
/*   Updated: 2020/12/18 10:42:49 by mkarkaus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "./includes/libft.h"
#include "../includes/lem_in.h"

int		**ft_tabarr_malloc(int max_rows, int max_cols)
{
	int		**tmp;
	int		i;

	i = -1;
	if (!(tmp = (int **)malloc((max_rows) * sizeof(int *))))
		return (NULL);
	// ft_printf("max_rows:%d  max_cols:%d\n", max_rows, max_cols);
	while (++i < max_rows)
	{
		// ft_printf("123   i:%d\n", i);
		if (!(tmp[i] = (int *)malloc((max_cols) * sizeof(int))))
			return (NULL);
		// ft_printf("456\n");
	}
	return (tmp);
}
