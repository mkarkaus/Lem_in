/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkarkaus <mkarkaus@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/22 12:38:45 by mkarkaus          #+#    #+#             */
/*   Updated: 2020/09/23 11:20:06 by mkarkaus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

typedef struct	s_hill
{
	char	**input;
	char	**name;
	int		*r_id;
	int		*res;
	char	**link;
	int		**coor;
}				t_hill;

/*
	name = names of the rooms
	res  = is room reserved by an ant (and by which ant)
	link = all the links from the room link[0]    mikko#maija#antti
*/

#endif