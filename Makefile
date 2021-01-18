# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sreijola <sreijola@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/12/19 17:36:20 by sreijola          #+#    #+#              #
#    Updated: 2021/01/18 15:35:19 by sreijola         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: all clean fclean re fun lem vis vfclean vre ltest

NAME = lem-in

VIS = exe

SRCS_C = lemin_main.c \
	lemin_get_data.c \
	lemin_get_rooms.c \
	lemin_get_links.c \
	lemin_validate_input.c \
	lemin_graph_maze.c \
	lemin_del_links.c \
	lemin_forks.c \
	lemin_forks_in.c \
	lemin_routes.c \
	lemin_print.c \
	ft_lstfree.c \
	ft_lstlen.c \
	ft_tabnequ.c \
	ft_tabarr_malloc.c \
	ft_tabarr_free.c \
	ft_tabint_find.c \
	ft_strarr_size.c \
	ft_strarr_free.c \
	ft_strarr_print.c \
	ft_graph_edgeadd.c \
	ft_graph_new.c \
	ft_graph_nodenew.c \
	ft_graph_free.c \
	ft_graph_print.c

#	lemin_move_ants.c

SRCS_PATH = ./srcs/

SRCS = $(addprefix $(SRCS_PATH), $(SRCS_C))

VIS_SRCS_CPP = main.cpp \
	get_input.cpp \
	ants.cpp \
	visualizer.cpp

VIS_SRCS_PATH = ./Visualizer/srcs/

VIS_SRCS = $(addprefix $(VIS_SRCS_PATH), $(VIS_SRCS_CPP))

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

lem:
	@gcc $(SRCS) $(LIB) -o $(NAME)
	@echo "$(NAME) made!"

relem:
	@rm -f $(NAME)
	@gcc $(SRCS) $(LIB) -o $(NAME)
	@echo "$(NAME) remade!"

lemf:
	@gcc $(SRCS) $(FLAGS) $(LIB) -o $(NAME)

vis: 
	@make -C Visualizer

#$(VIS)
#$(VIS):
# @g++ $(VIS_SRCS) -o $(VIS)
# @echo "Visualizer $(VIS) made"
#	g++ -o exe Visualizer/srcs/main.cpp Visualizer/srcs/get_input.cpp Visualizer/srcs/ants.cpp Visualizer/srcs/class_functions.cpp -lSDL2 -lSDL2_image -lSDL2_ttf
#	g++ -o exe srcs/main.cpp srcs/get_input.cpp srcs/ants.cpp srcs/class_functions.cpp -lSDL2 -lSDL2_image -lSDL2_ttf

vfclean:
	@make -C Visualizer fclean

vre:
	@make -C Visualizer re

etest:
	./maps/lemin_error.sh 

vtest:
	./maps/lemin_valid.sh 
