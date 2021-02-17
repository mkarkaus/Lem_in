/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin_validate_input.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sreijola <sreijola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/30 15:13:44 by mkarkaus          #+#    #+#             */
/*   Updated: 2021/02/17 16:06:23 by sreijola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

int		check_format(char *contents)
{
	int		i;

	i = 0;
	while (contents[i] != ' ' && contents[i] != '-' && contents[i] != '#')
		i++;
	if (contents[i] == ' ' && ft_isdigit(contents[i + 1]) && i != 0 && ++i)// contents[0] != 'L' tän pitää chekata myös se iso L
	{
		while (ft_isdigit(contents[i]))
			i++;
		if (contents[i] == ' ' && ft_isdigit(contents[i + 1]) && ++i)
			while (ft_isdigit(contents[i]))
				i++;
	}
	else if (contents[i] == '-' && contents[i + 1] && i != 0 && ++i) //sama tässä 0. ja viivan jälkeinen ei oo 'L'
		while (contents[i] && contents[i] != ' ' && contents[i] != '-')
			i++;
	else if ((contents[0] == '#' && contents[1] != '#') || \
				ft_strequ(contents, "##start") || ft_strequ(contents, "##end"))
		while (contents[i])
			i++;
	if (!contents[i] && contents[0] != 'L')
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
	int			rms_check;
	char		*s;

	rms_check = 0;
	start = 0;
	end = 0;
	while (lst != NULL && check_format(lst->content) && (start < 2 || end < 2))
	{
		s = lst->content;
		if (s[0] != '#' && s[0] != 'L' && !ft_strchr(s, '-') && rms_check == 0)
			ah->rooms++;
		else if (s[0] != '#' && s[0] != 'L' && !ft_strchr(s, '-'))
			return (-1);
		else if (ft_strchr(s, '-') && (rms_check = 1))
			ah->links++;
		else if (s[0] == '#' && s[1] == '#' && rms_check == 0 && \
				valid_start_end(&lst, &s, &start, &end) == -1)
			return (-1);
		lst = lst->next;
	}
	if (lst != NULL || start != 1 || end != 1 \
	|| ah->rooms == 0 || ah->links == 0)
		return (-1);
	return (0);
}
