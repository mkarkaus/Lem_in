/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin_data.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkarkaus <mkarkaus@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/25 12:42:03 by mkarkaus          #+#    #+#             */
/*   Updated: 2020/09/29 13:29:43 by mkarkaus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

void	init_struct(t_hill *ah)
{
	ah->ants = 0;
	ah->rooms = 0;
}

int		check_format(char *contents)
{
	int		i;

	i = 0;
	while (contents[i] != ' ' && contents[i] != '-' && contents[i] != '#')
		i++;
	if (contents[i] == ' ' && ft_isdigit(contents[i + 1]) && i != 0 && ++i)
	{
		while (ft_isdigit(contents[i]))
			i++;
		if (contents[i] == ' ' && ft_isdigit(contents[i + 1]) && ++i)
			while (ft_isdigit(contents[i]))
				i++;
	}
	else if (contents[i] == '-' && contents[i + 1] && i != 0 && ++i)
		while (contents[i] && contents[i] != ' ' && contents[i] != '-')
			i++;
	else if ((contents[0] == '#' && contents[1] != '#') || \
				ft_strequ(contents, "##start") || ft_strequ(contents, "##end"))
		while (contents[i])
			i++;
	if (!contents[i])
		return (1);
	return (0);
}

int		check_content(t_hill *ah, t_list *lst)
{
	int			start;
	int			end;
	int			rooms_checked;
	char		*str;

	rooms_checked = 0;
	start = 0;
	end = 0;
	while (lst != NULL && check_format(lst->content) && start < 2 || end < 2)
	{
		str = lst->content;
		if (str[0] != '#' && str[0] != 'L' && !ft_strchr(str, '-') && rooms_checked == 0)
			ah->rooms++;
		else if (str[0] != '#' && str[0] != 'L' && !ft_strchr(str, '-'))
			return (-1);
		else if (ft_strchr(str, '-'))
			rooms_checked = 1;
		else if (str[0] == '#' && str[1] == '#' && rooms_checked == 0)
		{
			if (ft_strequ(str, "##start"))
				start++;
			else if (ft_strequ(str, "##end"))
				end++;
			if (lst->next != NULL && (str = ((lst->next)->content)) && (str[0] == '#' || ft_strchr(str, '-')))
				return (-1);
		}
		lst = lst->next;
	}
	if (lst != NULL || start != 1 || end != 1 || ah->rooms == 0)
		return (-1);
	return (0);
}

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

int		get_data(t_hill *ah)
{
	t_list	*input;

	input = NULL;
	if (input_to_list(&input, ah) == -1)
		return (-1);
	if (check_content(ah, input) == -1)
		return (-1);
	// ft_lstprint(input);
	return (0);
}
