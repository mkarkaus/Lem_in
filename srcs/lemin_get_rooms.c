/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin_get_rooms.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sreijola <sreijola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/06 15:59:14 by mkarkaus          #+#    #+#             */
/*   Updated: 2020/10/07 11:28:39 by sreijola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

void	save_room_info(t_hill *ah, t_list **lst, int i)
{
	char	**temp;

	ah->coor[i] = (int *)ft_memalloc(sizeof(int) * 2);
	if (i < 2)
		*lst = (*lst)->next;
	temp = ft_strsplit((*lst)->content, ' ');
	ah->name[i] = ft_strdup(temp[0]);
	ah->coor[i][0] = ft_atoi(temp[1]);
	ah->coor[i][1] = ft_atoi(temp[2]);
	ft_strarr_free(temp);
}

void	get_rooms(t_hill *ah, t_list *lst)
{
	int		i;

	i = 2;
	ah->name = (char **)ft_memalloc((ah->rooms + 1) * sizeof(char *));
	ah->coor = (int **)ft_memalloc((ah->rooms) * sizeof(int *));
	while (i < ah->rooms)
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
}
