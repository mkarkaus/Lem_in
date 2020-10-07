/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tabarr_free.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sreijola <sreijola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/28 04:24:18 by sreijola          #+#    #+#             */
/*   Updated: 2020/10/07 11:26:19 by sreijola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "./includes/libft.h"
#include "../includes/lem_in.h"

void	ft_tabarr_free(int **tab, int max_rows)
{
	if (!tab)
		return ;
	while (--max_rows >= 0)
		free(tab[max_rows]);
	free(tab);
}
