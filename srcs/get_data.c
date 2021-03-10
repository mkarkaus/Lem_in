/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_data.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkarkaus <mkarkaus@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 12:54:57 by mkarkaus          #+#    #+#             */
/*   Updated: 2021/03/10 19:46:39 by mkarkaus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

void	init_struct(t_hill *ah)
{
	ah->ants = 0;
	ah->rooms = 0;
	ah->links = 0;
}

int		input_to_data(t_list **input, t_list **data, t_hill *ah)
{
	char	*tmp;
	t_list	*add;
	t_list	*it;

	it = *input;
	while (((char *)it->content)[0] == '#' && !(ft_strequ("##start", \
			it->content) || ft_strequ("##end", it->content)))
		it = it->next;
	ah->ants = ft_atoui(it->content);
	if (!ft_onlydigits(it->content) || ah->ants < 1 || ah->ants > INT_MAX)
		return (-1);
	it = it->next;
	while (it && (tmp = it->content) && ((tmp[0] == '#' && tmp[1] == '#'\
			&& !(ft_strequ("##start", tmp) || ft_strequ("##end", tmp)))\
			|| (tmp[0] == '#' && tmp[1] != '#')))
		it = it->next;
	add = ft_lstnew(it->content, ft_strlen(it->content) + 1);
	*data = add;
	while ((it = it->next) && it != NULL)
		if ((tmp = it->content) && !(tmp[0] == '#' && tmp[1] != '#') \
		&& !(tmp[0] == '#' && tmp[1] == '#' \
		&& !(ft_strequ("##start", tmp) || ft_strequ("##end", tmp))) && \
		(add->next = ft_lstnew(it->content, ft_strlen(it->content) + 1)))
			add = add->next;
	return (0);
}

int		save_input(t_list **head)
{
	t_list	*data;
	char	*temp;

	if (get_next_line(0, &temp, 0) < 1)
		return (-1);
	*head = ft_lstnew(temp, ft_strlen(temp) + 1);
	data = *head;
	free(temp);
	while ((get_next_line(0, &temp, 0)) > 0)
	{
		data->next = ft_lstnew(temp, ft_strlen(temp) + 1);
		data = data->next;
		ft_strdel(&temp);
	}
	return (0);
}

int		get_data(t_hill *ah, t_list **input)
{
	ah->data = NULL;
	init_struct(ah);
	if (save_input(input) == -1)
		return (-1);
	if (input_to_data(input, &ah->data, ah) == -1 \
	|| valid_content(ah, ah->data) == -1)
		return (-2);
	if (get_rooms(ah, ah->data) == -1)
		return (-3);
	if (get_links(ah->data, ah) == -1)
		return (-4);
	if (graph_maze(ah) == -1)
		return (-5);
	return (0);
}
