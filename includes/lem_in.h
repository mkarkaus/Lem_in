/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkarkaus <mkarkaus@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/22 12:38:45 by mkarkaus          #+#    #+#             */
/*   Updated: 2020/10/01 14:59:34 by mkarkaus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# include "../libft/includes/libft.h"

typedef struct	s_node
{
	int				room;
	struct s_node 	*next;
}				t_node;

typedef struct	s_alhead
{
	t_node			*head;
}				t_alhead;

typedef struct	s_graph
{
	int				ver;
	t_alhead		*array;
}				t_graph;

typedef struct	s_hill
{
	int			ants;
	int			rooms;
	char		**name;
	int			**coor;
	int			*r_id;
	int			links;
	int			**link;
	int			*res;
}				t_hill;

void			ft_strarr_print(char **arr);


void			init_struct(t_hill *ah);
int				get_data(t_hill *ah);
int				valid_content(t_hill *ah, t_list *lst);

/*
	name = names of the rooms
	res  = is room reserved by an ant (and by which ant)
	link = all the links from the room link[0]    mikko#maija#antti
*/

#endif
