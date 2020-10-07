# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sreijola <sreijola@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/12/19 17:36:20 by sreijola          #+#    #+#              #
#    Updated: 2020/10/07 11:15:09 by sreijola         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: all clean fclean re fun lem

NAME = lem-in

SRCS_C = lemin_main.c \
	lemin_get_data.c \
	lemin_get_rooms.c \
	lemin_get_links.c \
	lemin_validate_input.c \
	lemin_graph_maze.c \
	ft_lstfree.c\
	ft_tabarr_free.c \
	ft_strarr_size.c \
	ft_strarr_free.c \
	ft_strarr_print.c \
	ft_graph_edgeadd.c \
	ft_graph_new.c \
	ft_graph_nodenew.c \
	ft_graph_free.c \
	ft_graph_print.c

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

lem:
	@gcc $(SRCS) $(LIB) -o $(NAME)

lemf:
	@gcc $(SRCS) $(FLAGS) $(LIB) -o $(NAME)
