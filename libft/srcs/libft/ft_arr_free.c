/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arr_free.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkarkaus <mkarkaus@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/05 11:18:11 by sreijola          #+#    #+#             */
/*   Updated: 2021/03/05 11:22:31 by mkarkaus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

void	ft_arr_free(void **tab, int max_rows)
{
	if (!tab)
		return ;
	while (--max_rows >= 0)
		free(tab[max_rows]);
	free(tab);
}
