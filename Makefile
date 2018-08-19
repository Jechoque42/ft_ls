# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jechoque <jbchoquet@gmail.com>             +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/12/05 03:47:19 by jechoque          #+#    #+#              #
#    Updated: 2017/12/19 16:04:57 by jechoque         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_ls

FLAGS = -Wall -Wextra -Werror -O3

HDR = ./include/ft_ls.h

SRC = ./src/main.c \
	./src/ft_ls_create.c \
	./src/ft_ls_del.c \
	./src/ft_ls_error.c \
	./src/ft_ls_display.c \
	./src/ft_ls_options.c \
	./src/ft_ls_padding.c \
	./src/ft_ls_parse.c \
	./src/ft_ls_sort.c \
	./src/ft_ls_tree.c \

LIB =	./libftprintf/libft/libft.a ./libftprintf/libftprintf.a

OBJ = ./main.o \
	./ft_ls_create.o \
	./ft_ls_del.o \
	./ft_ls_error.o \
	./ft_ls_display.o \
	./ft_ls_options.o \
	./ft_ls_padding.o \
	./ft_ls_parse.o \
	./ft_ls_sort.o \
	./ft_ls_tree.o \

all: $(NAME)

$(NAME): $(SRC) $(HDR)
	@make -C ./libftprintf/
	@gcc $(FLAGS) -o $(NAME) $(SRC) $(LIB)
	@echo "###########################"
	@echo "##  ___ ___    _    ___  ##"
	@echo "##  |_   |     |   (__   ##"
	@echo "##  |    | ___ |__ ___)  ##"
	@echo "##                       ##"
	@echo "###########################"
	@echo "\033[1;34mft_ls\t\033[1;33mCompilation\t\033[0;32m[OK]\033[0m"

clean:
	@make -C ./libftprintf clean
	@rm -rf $(OBJ)
	@echo "\033[1;34mft_ls\t\033[1;33mCleaning obj\t\033[0;32m[OK]\033[0m"

fclean: clean
	@make -C ./libftprintf fclean
	@rm -rf $(NAME)
	@echo "\033[1;34mft_ls\t\033[1;33mCleaning lib\t\033[0;32m[OK]\033[0m"

re: fclean all
