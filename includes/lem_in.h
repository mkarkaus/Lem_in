/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkarkaus <mkarkaus@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/22 12:38:45 by mkarkaus          #+#    #+#             */
/*   Updated: 2020/09/28 16:41:47 by mkarkaus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# include "../libft/includes/libft.h"

typedef struct	s_hill
{
	char		**input;
	char		**name;
	int			*r_id;
	int			*res;
	int			ants;
	int			rooms;
	char		**link;
	int			**coor;
}				t_hill;

// t_list			*input_to_list(t_list *head);
void			get_data(t_hill *ah);

/*
	name = names of the rooms
	res  = is room reserved by an ant (and by which ant)
	link = all the links from the room link[0]    mikko#maija#antti
*/

#endif