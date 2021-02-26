/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tabarr_free.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkarkaus <mkarkaus@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/28 04:24:18 by sreijola          #+#    #+#             */
/*   Updated: 2021/02/26 11:36:40 by mkarkaus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

void	ft_tabarr_free(int **tab, int max_rows)
{
	if (!tab)
		return ;
	while (--max_rows >= 0)
		free(tab[max_rows]);
	free(tab);
}
