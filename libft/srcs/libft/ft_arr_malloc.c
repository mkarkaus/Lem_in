/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arr_malloc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkarkaus <mkarkaus@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/05 14:59:11 by mkarkaus          #+#    #+#             */
/*   Updated: 2021/03/05 15:36:03 by mkarkaus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

void	**ft_arr_malloc(unsigned long ptrs, unsigned long bytes)
{
	void				**tmp;
	unsigned long int	i;

	i = -1;
	if (!(tmp = ft_memalloc(ptrs * sizeof(void *))))
		return (NULL);
	while (++i < ptrs)
	{
		if (!(tmp[i] = ft_memalloc(bytes)))
			return (NULL);
	}
	return (tmp);
}
