/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkarkaus <mkarkaus@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/26 14:36:47 by mkarkaus          #+#    #+#             */
/*   Updated: 2021/03/08 18:01:21 by mkarkaus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# include "../libft/includes/libft.h"
# include <limits.h>
# include <time.h>//DELETE

/*
**	Defines how many times bfs-search is performed
*/
# define SEARCH_TIMES 5

/*
**	Defines maximum route length
*/
# define LEN_MAX 120

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
	int				ver;
	int				paths;
	unsigned int	**best_set;
	unsigned int	**set;
	int				**route;
	unsigned int	**used;
	int				*been;
	int				*res;
	int				*flow;
	int				start_to_end;
	t_alhead		*array;
}				t_graph;

typedef struct	s_hill
{
	t_list			**moves;
	unsigned int	best_turns;
	t_graph			*maze;
	t_list			*input;
	t_list			*data;
	unsigned int	ants;
	int				rooms;
	char			**name;
	int				links;
	int				**link;
	int				*flags;
}				t_hill;

void			ft_graph_free(t_graph *graph);
void			ft_graph_print(t_graph *graph, char **name);
t_node			*ft_graph_nodenew(int dest_ver);
t_graph			*ft_graph_new(int vertices);
void			ft_graph_edgeadd(t_graph *graph, int a, int b, int dir);
void			parse_flags(t_hill *ah);
int				save_flags(char **av, t_hill *ah);
int				valid_content(t_hill *ah, t_list *lst);
int				get_data(t_hill *ah, t_list **input);
int				get_rooms(t_hill *ah, t_list *lst);
int				get_links(t_list *lst, t_hill *ah);
int				graph_maze(t_hill *ah);
int				count_potential_paths(t_graph *maze);
void			init_routes(t_graph *maze);
int				find_route_sets(t_graph *maze, unsigned int ants);
void			init_sets(t_graph *maze);
void			create_set(t_graph *maze, unsigned int ants);
void			add_to_route(t_graph *maze, int prev_room, int *row, int len);
void			create_moves(t_hill *ah);

#endif
