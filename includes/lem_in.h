/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sreijola <sreijola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/22 12:38:45 by mkarkaus          #+#    #+#             */
/*   Updated: 2020/10/07 11:31:03 by sreijola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# include "../libft/includes/libft.h"

typedef struct	s_node
{
	int				v;
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
	t_graph		*maze;
	int			ants;
	int			rooms;
	char		**name;
	int			**coor;
	int			links;
	int			**link;
}				t_hill;

int				get_data(t_hill *ah);
void			init_struct(t_hill *ah);
void			get_rooms(t_hill *ah, t_list *lst);
int				get_links(t_list *lst, t_hill *ah);
int				valid_content(t_hill *ah, t_list *lst);
void			graph_maze(t_hill *ah);

void			ft_lstfree(t_list *lst);

void			ft_tabarr_free(int **tab, int max_rows);

int				ft_strarr_size(char **arr);
void			ft_strarr_free(char **arr);
void			ft_strarr_print(char **arr);

void			ft_graph_free(t_graph *graph);
void			ft_graph_print(t_graph *graph);
t_node			*ft_graph_nodenew(int dest_ver);
t_graph			*ft_graph_new(int vertices);
void			ft_graph_edgeadd(t_graph *graph, int a, int b, int dir);

/*
	name = names of the rooms
	res  = is room reserved by an ant (and by which ant)
	link = all the links from the room link[0]    mikko#maija#antti
*/

#endif
