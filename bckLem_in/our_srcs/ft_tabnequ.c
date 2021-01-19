/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tabnequ.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sreijola <sreijola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 13:48:54 by sreijola          #+#    #+#             */
/*   Updated: 2020/11/02 14:20:54 by sreijola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"
//#include "../../includes/libft.h"

int		ft_tabnequ(int *t1, int *t2, int n)
{
	int	i;

	i = 0;
	if (!t1 || !t2)
		return (0);
	while (i < n && t1[i] == t2[i]) //t1[i] && t2[i]
		i++;
	if (i == n)// && !t1[i] && !t2[i])
		return (1);
	return (0);
}
