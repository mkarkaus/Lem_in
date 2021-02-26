/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkarkaus <mkarkaus@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/26 14:36:47 by mkarkaus          #+#    #+#             */
/*   Updated: 2021/02/26 14:39:44 by mkarkaus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# include "../libft/includes/libft.h"
# include <limits.h>

/*
**	Defines how many times bfs-search is performed
*/
# define SEARCH_TIMES 30

/*
**	Defines maximum route length
*/
# define LEN_MAX 100

typedef struct	s_node
{
	int				v;
	struct s_node	*next;
}				t_node;

typedef struct	s_alhead
{
	t_node			*head;
}				t_alhead;

typedef struct	s_graph
{
	int				**used;
	int				*been;
	int				*flow;
	int				paths;
	int				start_to_end;
	int				ver;
	int				**best_set;
	int				**set;
	int				**route;
	t_alhead		*array;
}				t_graph;

typedef struct	s_hill
{
	t_list			**moves;
	int				best_turns;
	t_graph			*maze;
	t_list			*input;
	t_list			*data;
	int				ants;
	int				rooms;
	char			**name;
	int				**coor;
	int				links;
	int				**link;
	int				*flags;
}				t_hill;

void			ft_graph_free(t_graph *graph);
void			ft_graph_print(t_graph *graph, char **name);
t_node			*ft_graph_nodenew(int dest_ver);
t_graph			*ft_graph_new(int vertices);
void			ft_graph_edgeadd(t_graph *graph, int a, int b, int dir);

int				print_options(int *flags);
void			print_routes(int **routes, int paths, char **names);
void			print_stats(int rms, int links, int ants);
void			parse_flags(t_hill *ah);
int				save_flags(char **av, t_hill *ah);

void			del_edge(t_node **head, t_node **del);
void			del_deadends(t_graph *maze);
void			fill_distances(t_hill *ah);
int				graph_maze(t_hill *ah);
int				get_links(t_list *lst, t_hill *ah);
int				get_rooms(t_hill *ah, t_list *lst);
int				get_data(t_hill *ah, t_list **input);
void			init_struct(t_hill *ah);
int				valid_content(t_hill *ah, t_list *lst);
void			print_moves(t_hill *ah);
int				count_potential_paths(t_graph *maze);
void			init_routes(t_graph *maze);
void			sort_routes(int ***route, int max_paths);
void			route_length(int **route);
void			add_to_route(t_graph *maze, int prev_room, int *row, int len);
int				find_route_sets(t_graph *maze, int ants);
void			init_sets(t_graph *maze);
void			create_set(t_graph *maze, int ants);
void			del_route(t_graph *maze, int del);

#endif
