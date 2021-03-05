/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_rooms.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkarkaus <mkarkaus@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 12:55:16 by mkarkaus          #+#    #+#             */
/*   Updated: 2021/03/05 12:49:26 by mkarkaus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

void	save_room_info(t_hill *ah, t_list **lst, int k)
{
	char	*temp;
	int		len;
	int		i;

	len = 0;
	if (k < 2)
		*lst = (*lst)->next;
	temp = (*lst)->content;
	while (temp[len] != ' ')
		len++;
	if (!(ah->name[k] = (char *)malloc((len + 1) * sizeof(char))))
		return ;
	i = 0;
	while (i < len)
	{
		ah->name[k][i] = temp[i];
		i++;
	}
	ah->name[k][i] = '\0';
}

int		check_doubles(t_hill *ah)
{
	int		i;
	int		j;

	i = -1;
	while (++i < ah->rooms)
	{
		j = i;
		while (++j < ah->rooms)
		{
			if (ft_strequ(ah->name[i], ah->name[j]))
				return (1);
		}
	}
	return (0);
}

int		get_rooms(t_hill *ah, t_list *lst)
{
	int		i;
	int		j;

	j = -1;
	i = 2;
	ah->name = (char **)ft_memalloc((ah->rooms + 1) * sizeof(char *));
	while (++j < ah->rooms)
	{
		if (ft_strequ(lst->content, "##start"))
			save_room_info(ah, &lst, 0);
		else if (ft_strequ(lst->content, "##end"))
			save_room_info(ah, &lst, 1);
		else
			save_room_info(ah, &lst, i++);
		lst = lst->next;
	}
	ah->name[ah->rooms] = NULL;
	if (check_doubles(ah))
		return (-1);
	return (0);
}
