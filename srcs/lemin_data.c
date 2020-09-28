/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_data.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkarkaus <mkarkaus@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/25 12:42:03 by mkarkaus          #+#    #+#             */
/*   Updated: 2020/09/28 15:19:33 by mkarkaus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

void	input_to_list(t_list **head)
{
	t_list	*data;
	t_list	*app;
	char	*temp;
	int		ants;

	get_next_line(0, &temp, 0);
	ants = ft_atoi(temp);
	get_next_line(0, &temp, 0);
	data = ft_lstnew(temp, ft_strlen(temp) + 1);
	data->content = ft_strdup(temp);
	while (get_next_line(0, &temp, 0) > 0)
	{
		app = ft_lstnew(temp, ft_strlen(temp) + 1 + sizeof(size_t));
		app->content = ft_strdup(temp);
		if (!(*head))
			*head = data;
		data->next = app;
		data = data->next;
	}
}

void	get_data()
{
	t_list	*input;

	input = NULL;
	input_to_list(&input);
	ft_lstprint(input);
}
