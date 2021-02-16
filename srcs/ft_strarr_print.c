/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strarr_print.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sreijola <sreijola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/27 18:57:05 by sreijola          #+#    #+#             */
/*   Updated: 2021/02/16 14:14:40 by sreijola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

void	ft_strarr_print(char **arr)
{
	int i;

	i = -1;
	while (arr[++i] != NULL)
		ft_printf("%s\n", arr[i]);
	ft_printf("\n");
}
