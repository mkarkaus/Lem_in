/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_ptr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkarkaus <mkarkaus@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 11:30:54 by mkarkaus          #+#    #+#             */
/*   Updated: 2020/08/27 17:41:00 by mkarkaus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../../includes/libft.h"

char		*ft_itoa(int n)
{
	char	*fresh;
	int		i;
	int		k;

	i = ft_intlen(n);
	k = i;
	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	if (!(fresh = (char *)malloc((i + 1) * sizeof(char))))
		return (0);
	if (n == 0)
		fresh[0] = '0';
	if (n < 0)
	{
		fresh[0] = '-';
		n = n * -1;
	}
	while (n > 0)
	{
		i--;
		fresh[i] = n % 10 + '0';
		n = n / 10;
	}
	fresh[k] = '\0';
	return (fresh);
}
