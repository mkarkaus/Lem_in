/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin_get_links.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkarkaus <mkarkaus@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/06 16:01:49 by mkarkaus          #+#    #+#             */
/*   Updated: 2020/10/29 15:32:33 by mkarkaus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

int		convert_link(char *str, t_hill *ah, int k)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	ah->link[k] = (int *)ft_memalloc(sizeof(int) * 2);
	while (str[j] != '-')
		j++;
	while (ah->name[i] != NULL && ft_strnequ(ah->name[i], str, j) == 0)
		i++;
	ah->link[k][0] = i;
	i = 0;
	while (ah->name[i] != NULL && ft_strequ(ah->name[i], str + j + 1) == 0)
		i++;
	ah->link[k][1] = i;
	// ft_strarr_print(ah->name);
	// ft_printf("!!! [%s] !!!", str);
	if (ah->name[i] == NULL)
		return (-1);
	return (0);
}

int		get_links(t_list *lst, t_hill *ah)
{
	int		k;
	char	*tmp;

	k = 0;
	ah->link = (int **)ft_memalloc(ah->links * sizeof(int *));
	while (lst != NULL && (tmp = lst->content) && ft_strchr(tmp, '-') == NULL)
		lst = lst->next;
	while (lst != NULL && (tmp = lst->content) \
			&& (ft_strchr(tmp, '-') != NULL) && tmp[0] != 'L')
	{
		if (convert_link(tmp, ah, k) == -1)
			return (-1);
		// ft_pr_intarr(ah->link, k + 1, 2, 1);
		lst = lst->next;
		k++;
	}
	return (0);
}