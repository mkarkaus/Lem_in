/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin_data.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sreijola <sreijola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/25 12:42:03 by mkarkaus          #+#    #+#             */
/*   Updated: 2020/09/30 18:17:58 by sreijola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

int		input_to_list(t_list **head, t_hill *ah)
{
	t_list	*data;
	t_list	*app;
	char	*temp;

	get_next_line(0, &temp, 0);
	ah->ants = ft_atoi(temp);
	if (!ft_onlydigits(temp))
		return (-1);
	get_next_line(0, &temp, 0);
	data = ft_lstnew(temp, ft_strlen(temp) + 1);
	data->content = temp;
	while (get_next_line(0, &temp, 0) > 0)
	{
		app = ft_lstnew(temp, ft_strlen(temp) + 1);
		app->content = temp;
		if (!(*head))
			*head = data;
		data->next = app;
		data = data->next;
	}
	return (0);
}

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
}

int		get_rooms(t_hill *ah, t_list *lst)
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
		{
			save_room_info(ah, &lst, i);
			i++;
		}
		lst = lst->next;
	}
	ah->name[ah->rooms] = NULL;
	return (0);
}

int		get_data(t_hill *ah)
{
	t_list	*input;

	input = NULL;
	if (input_to_list(&input, ah) == -1 || valid_content(ah, input) == -1)
		return (-1);
	/* HERE COMES THE GET_ROOMS */
	get_rooms(ah, input);
	ft_lstprint(input);
	//ft_printf("%s\n", ah->name[0]);
	ft_strarr_print(ah->name);
	ft_pr_intarr(ah->coor, ah->rooms, 2, 1);
	return (0);
}
