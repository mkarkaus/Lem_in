/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strarr_free.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkarkaus <mkarkaus@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/27 18:53:34 by sreijola          #+#    #+#             */
/*   Updated: 2020/09/30 16:49:30 by mkarkaus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

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
