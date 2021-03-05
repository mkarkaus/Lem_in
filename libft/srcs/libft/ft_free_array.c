/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_array.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkarkaus <mkarkaus@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/02 11:13:33 by mkarkaus          #+#    #+#             */
/*   Updated: 2021/03/05 15:26:21 by mkarkaus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

void	ft_free_arrays(void **ptr, int rows)
{
	int		i;

	i = -1;
	while (++i < rows)
		free(ptr[i]);
	free(ptr);
}
