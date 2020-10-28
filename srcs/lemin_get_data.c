/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin_get_data.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkarkaus <mkarkaus@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/25 12:42:03 by mkarkaus          #+#    #+#             */
/*   Updated: 2020/10/28 13:57:46 by mkarkaus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

void	init_struct(t_hill *ah)
{
	ah->ants = 0;
	ah->rooms = 0;
	ah->links = 0;
}

int		input_to_list(t_list **head, t_hill *ah)
{
	t_list	*data;
	t_list	*app;
	char	*temp;
	int		ret;

	get_next_line(0, &temp, 0);
	ah->ants = ft_atoi(temp);
	if (!ft_onlydigits(temp) || ah->ants == 0)
		return (-1);
	free(temp);
	while (get_next_line(0, &temp, 0) && temp[0] == '#' && temp[1] != '#')
		free(temp);
	data = ft_lstnew(temp, ft_strlen(temp) + 1);
	*head = data;
	free(temp);
	while ((ret = get_next_line(0, &temp, 0)) > 0)
	{
		if (!(temp[0] == '#' && temp[1] != '#'))
		{
			app = ft_lstnew(temp, ft_strlen(temp) + 1);
			data->next = app;
			data = data->next;
		}
		ft_strdel(&temp);
	}
	return (0);
}

int		get_data(t_hill *ah)
{
	t_list	*input;

	input = NULL;
	init_struct(ah);
	if (input_to_list(&input, ah) == -1 || valid_content(ah, input) == -1)
		return (-1);
	// ft_printf("a:[%d]r:[%d]l:[%d]\n", ah->ants, ah->rooms, ah->links); //tää heiluu hulluja
	get_rooms(ah, input);
	if (get_links(input, ah) == -1)
		return (-1);
	ft_printf("%d\n", ah->ants);
	ft_lstprint(input);
	write(1, "\n", 1);
	// ft_strarr_print(ah->name);
	// ft_pr_intarr(ah->link, ah->links, 2, 1);
	ft_lstfree(input);
	graph_maze(ah);
	// ft_graph_print(ah->maze);
	return (0);
}
