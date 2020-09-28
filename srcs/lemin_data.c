/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin_data.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkarkaus <mkarkaus@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/25 12:42:03 by mkarkaus          #+#    #+#             */
/*   Updated: 2020/09/28 16:42:03 by mkarkaus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

// void	init_struct(t_hill *ah)
// {
// 	ah->ants = 0;
// 	ah->rooms = 0;
// }

// int		analyze_data(t_hill *ah, char *inp)
// {
// 	int		i;
// 	int		cmd;

// 	i = 0;
// 	cmd = 0;
// 	if ((ft_strnequ("##start", inp, 7) && (cmd = 1)) || 
// 		(ft_strnequ("##end", inp, 5) && (cmd = 2)))
// 		get_next_line(0, &inp, 0);
// 	if ()
// 	{

// 	}
// }

// int		input_to_list(t_hill *ah)
// {
// 	char	*temp;

// 	get_next_line(0, &temp, 0);
// 	ah->ants = ft_atoi(temp);
// 	while (analyze_data(ah, temp) == 1)
// 		get_next_line(0, &temp, 0);
// 	while (analyze_data(ah, temp) == 2)
// 		get_next_line(0, &temp, 0);
// }

void	input_to_list(t_list **head, t_hill *ah)
{
	t_list	*data;
	t_list	*app;
	char	*temp;

	get_next_line(0, &temp, 0);
	ah->ants = ft_atoi(temp);
	get_next_line(0, &temp, 0);
	data = ft_lstnew(temp, ft_strlen(temp) + 1);
	data->content = ft_strdup(temp);
	while (get_next_line(0, &temp, 0) > 0)
	{
		app = ft_lstnew(temp, ft_strlen(temp) + 1 + sizeof(size_t));
		app->content = temp;
		if (!(*head))
			*head = data;
		data->next = app;
		data = data->next;
	}
}

void	get_data(t_hill *ah)
{
	t_list	*input;

	input = NULL;
	input_to_list(&input, ah);
	ft_lstprint(input);
}
