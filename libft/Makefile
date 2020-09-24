# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mkarkaus <mkarkaus@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/30 11:50:18 by mkarkaus          #+#    #+#              #
#    Updated: 2020/09/24 12:40:43 by mkarkaus         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

FT_PRINTF_SRC_PATH = ./srcs/ft_printf/
FT_PRINTF_SRC_FILES = ft_printf.c parse_format.c struct_edit.c float_types.c \
integer_types.c optional_flags.c precision_width.c other_float_types.c \
pointer_types.c

FT_PRINTF_SRC = $(addprefix $(FT_PRINTF_SRC_PATH), $(FT_PRINTF_SRC_FILES))

LIBFT_SRC_PATH = ./srcs/libft/
LIBFT_SRC_FILES = ft_isalnum.c ft_memalloc.c ft_memmove.c ft_putnbr.c ft_strclr.c \
ft_striter.c ft_strmapi.c ft_strrchr.c ft_toupper.c ft_isalpha.c ft_memccpy.c \
ft_memset.c ft_putnbr_fd.c ft_strcmp.c ft_striteri.c ft_strncat.c \
ft_strsplit.c ft_isascii.c ft_memchr.c ft_putchar.c ft_putstr.c ft_strcpy.c \
ft_strjoin.c ft_strncmp.c ft_strstr.c ft_isdigit.c ft_memcmp.c \
ft_putchar_fd.c ft_putstr_fd.c ft_strdel.c ft_tolower.c ft_strncpy.c \
ft_strsub.c ft_atoi.c ft_isprint.c ft_memcpy.c ft_putendl.c ft_strcat.c \
ft_strdup.c ft_strlen.c ft_strnequ.c ft_strtrim.c ft_bzero.c ft_itoa.c \
ft_memdel.c ft_putendl_fd.c ft_strchr.c ft_strequ.c ft_strmap.c ft_strnew.c \
ft_strlcat.c ft_strnstr.c ft_lstnew.c ft_lstdelone.c ft_lstdel.c ft_lstadd.c \
ft_lstiter.c ft_lstmap.c ft_intlen.c ft_isupper.c ft_islower.c ft_swap.c \
ft_isspace.c ft_longlen.c ft_itoa_llong.c ft_intlen_llong.c ft_itoa_ptr.c \
ft_strrev.c ft_strcut.c ft_onlydigits.c ft_free_array.c ft_pr_intarr.c \
ft_pr_chararr.c ft_lstapp.c ft_lstprint.c

LIBFT_SRC = $(addprefix $(LIBFT_SRC_PATH), $(LIBFT_SRC_FILES))

GNL_SRC_PATH = ./srcs/get_next_line/
GNL_SRC_FILES = get_next_line.c

GNL_SRC = $(addprefix $(GNL_SRC_PATH), $(GNL_SRC_FILES))

FLAGS = -Wall -Werror -Wextra

HEAD = libft.h get_next_line.h ft_printf.h colors.h

OBJ = $(patsubst %.c, %.o, $(LIBFT_SRC_FILES) $(FT_PRINTF_SRC_FILES) \
$(GNL_SRC_FILES))

all: $(NAME)

$(NAME):
	@gcc -c $(FLAGS) $(FT_PRINTF_SRC) $(LIBFT_SRC) $(GNL_SRC)
	@ar rc $(NAME) $(OBJ)
	@echo "Archive file '$(NAME)' and object files for it CREATED."

clean:
	@/bin/rm -f $(OBJ)
	@echo "Object files for '$(NAME)' REMOVED."

fclean: clean
	@/bin/rm -f $(NAME)
	@echo "Archive file '$(NAME)' REMOVED."

re: fclean all
