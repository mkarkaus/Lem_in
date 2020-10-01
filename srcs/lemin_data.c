/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin_data.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkarkaus <mkarkaus@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/25 12:42:03 by mkarkaus          #+#    #+#             */
/*   Updated: 2020/10/01 14:59:37 by mkarkaus         ###   ########.fr       */
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
	while (get_next_line(0, &temp, 0) && temp[0] == '#' && temp[1] != '#')
		free(temp);
	data = ft_lstnew(temp, ft_strlen(temp) + 1);
	*head = data;
	while (get_next_line(0, &temp, 0) > 0)
	{
		if (!(temp[0] == '#' && temp[1] != '#'))
		{
			app = ft_lstnew(temp, ft_strlen(temp) + 1);
			data->next = app;
			data = data->next;
		}
		free(temp);
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

int		convert_link(char *str, t_hill *ah, int k)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	ah->link[k] = (int *)ft_memalloc(sizeof(int) * 2);
	while (str[j] != '-')
		j++;
	while (ah->name[i] != NULL && ft_strnequ(ah->name[i], str, j) == 0)
		i++;
	ah->link[k][0] = i;
	i = 0;
	while (ah->name[i] != NULL && ft_strequ(ah->name[i], str + j + 1) == 0 )
		i++;
	ah->link[k][1] = i;
	if (ah->name[i] == NULL)
		return (-1);
	return (0);
}

int		get_links(t_list *lst, t_hill *ah)
{
	int		k;
	char	*tmp;

	k = 0;
	ah->link = (int **)ft_memalloc(ah->links * sizeof(int *));
	while (lst != NULL && (tmp = lst->content) && ft_strchr(tmp, '-') == NULL)
		lst = lst->next;
	while (lst != NULL && (tmp = lst->content) && (ft_strchr(tmp, '-') != NULL) && tmp[0] != 'L')
	{
		ft_lstprint(lst);
		if (convert_link(tmp, ah, k) == -1)
			return (-1);
		ft_pr_intarr(ah->link, k + 1, 2, 1);
		ft_printf("\n");
		lst = lst->next;
		k++;
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
	// ft_lstprint(input);
	// ft_printf("a:[%d]r:[%d]l:[%d]\n", ah->ants, ah->rooms, ah->links); //tää heiluu hulluja
	get_rooms(ah, input);
	if (get_links(input, ah) == -1)
		return (-1);
	// ft_printf("[%d]\n", sizeof(int));
	// ft_printf("[%d]\n", sizeof(t_graph));
	// ft_printf("[%d]\n", sizeof(t_node));
	// ft_printf("[%d]\n", sizeof(t_alhead));
	// create_graph(ah);
	// ft_strarr_print(ah->name);
	// ft_pr_intarr(ah->coor, ah->rooms, 2, 1);
	// ft_pr_intarr(ah->link, ah->links, 2, 1);
	return (0);
}
