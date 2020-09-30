/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkarkaus <mkarkaus@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/30 15:13:44 by mkarkaus          #+#    #+#             */
/*   Updated: 2020/09/30 16:06:18 by mkarkaus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

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

int		valid_start_end(t_list **lst, char **str, int *start, int *end)
{
	if (ft_strequ(*str, "##start"))
		(*start)++;
	else if (ft_strequ(*str, "##end"))
		(*end)++;
	if ((*lst)->next == NULL || ((*str = ((*lst)->next->content)) && \
		(*str[0] == '#' || ft_strchr(*str, '-'))))
		return (-1);
	return (0);
}

int		valid_content(t_hill *ah, t_list *lst)
{
	int			start;
	int			end;
	int			rooms_checked;
	char		*str;

	rooms_checked = 0;
	start = 0;
	end = 0;
	while (lst != NULL && check_format(lst->content) && (start < 2 || end < 2))
	{
		str = lst->content;
		if (str[0] != '#' && str[0] != 'L' && !ft_strchr(str, '-') && rooms_checked == 0)
			ah->rooms++;
		else if (str[0] != '#' && str[0] != 'L' && !ft_strchr(str, '-'))
			return (-1);
		else if (ft_strchr(str, '-'))
			rooms_checked = 1;
		else if (str[0] == '#' && str[1] == '#' && rooms_checked == 0 && \
				valid_start_end(&lst, &str, &start, &end) == -1)
			return (-1);
		lst = lst->next;
	}
	if (lst != NULL || start != 1 || end != 1 || ah->rooms == 0)
		return (-1);
	return (0);
}
