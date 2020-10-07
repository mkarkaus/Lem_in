/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strarr_free.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sreijola <sreijola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/27 18:53:34 by sreijola          #+#    #+#             */
/*   Updated: 2020/10/06 19:17:59 by sreijola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"
//#include "./includes/libft.h"

void	ft_strarr_free(char **arr)
{
	int	rows;

	rows = ft_strarrsize(arr);
	while (rows > -1)
	{
		ft_strdel(&arr[rows]);
		rows--;
	}
	free(arr);
	arr = NULL;
}
