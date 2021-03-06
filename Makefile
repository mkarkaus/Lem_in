# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mkarkaus <mkarkaus@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/12/19 17:36:20 by sreijola          #+#    #+#              #
#    Updated: 2021/03/09 16:26:11 by mkarkaus         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: all clean fclean re fun vis vfclean vre relem etest vtest vetest vvtest

NAME = lem-in

SRCS_C = main.c \
	flags.c \
	validate_input.c \
	get_data.c \
	get_rooms.c \
	get_links.c \
	graph_maze.c \
	graph_utils.c \
	bfs.c \
	bfs_utils.c \
	create_set.c \
	build_route.c \
	flow_utils.c \
	print.c

SRCS_PATH = ./srcs/

SRCS = $(addprefix $(SRCS_PATH), $(SRCS_C))

LIB = libft/libft.a

FLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME):
	@make -C libft
	@gcc $(SRCS) $(FLAGS) $(LIB) -o $(NAME)
	@echo "Library and $(NAME) made"

clean:
	@make -C libft clean
	@echo "Object files removed from libft. Beep-Bop"

fclean:
	@make -C libft fclean
	@rm -f $(NAME)
	@echo "Binaries and object files gone."

re: fclean all
	@echo "All good again"
	
fun: re 
	@make -C libft clean
	@echo "Only binaries and .cs left"

relem:
	@rm -f $(NAME)
	@gcc $(SRCS) $(LIB) -o $(NAME)
	@echo "$(NAME) remade!"

vis: 
	@make -C Visualizer
	@cp lem-in Visualizer/ 

vfclean:
	@make -C Visualizer fclean

vre:
	@make -C Visualizer re

etest:
	./maps/lemin_error.sh 

vetest:
	./maps/lemin_error_val.sh

vtest:
	./maps/lemin_valid.sh 

vvtest:
	./maps/lemin_valid_val.sh
