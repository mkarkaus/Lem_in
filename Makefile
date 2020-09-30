# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mkarkaus <mkarkaus@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/12/19 17:36:20 by sreijola          #+#    #+#              #
#    Updated: 2020/09/30 16:52:37 by mkarkaus         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: all clean fclean re fun lem

NAME = lem-in

SRCS_C = lemin_main.c lemin_data.c validate_input.c

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
