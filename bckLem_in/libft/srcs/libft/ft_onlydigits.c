/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_onlydigits.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkarkaus <mkarkaus@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/09 16:15:41 by mkarkaus          #+#    #+#             */
/*   Updated: 2020/08/27 17:44:31 by mkarkaus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

int		ft_onlydigits(char *str)
{
	int		i;

	i = 0;
	while (str[i] && ft_isdigit(str[i]))
		i++;
	if (!str[i])
		return (1);
	return (0);
}
