/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strarr_size.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sreijola <sreijola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/24 13:42:15 by sreijola          #+#    #+#             */
/*   Updated: 2020/10/06 19:18:15 by sreijola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"
//#include "./includes/libft.h"

int		ft_strarr_size(char **arr)
{
	size_t i;

	i = 0;
	while (arr[i] != NULL)
		i++;
	return (i);
}
