/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sreijola <sreijola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/22 12:38:45 by mkarkaus          #+#    #+#             */
/*   Updated: 2020/09/30 21:58:32 by sreijola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# include "../libft/includes/libft.h"

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
