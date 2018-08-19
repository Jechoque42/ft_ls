# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jechoque <jbchoquet@gmail.com>             +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/11/24 14:11:16 by jechoque          #+#    #+#              #
#    Updated: 2017/12/19 15:45:01 by jechoque         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a

FLAGS = -Wall -Wextra -Werror -O3

SRC = ./src/util/ft_printf_handlers.c\
	./src/util/ft_printf_color.c\
	./src/util/ft_printf_parser.c\
	./src/util/ft_printf_utility.c\
	./src/util/ft_printf_buff_utility.c\
	./src/conv/ft_printf_conv_generic.c\
	./src/conv/ft_printf_conv_scpercent.c\
	./src/conv/ft_printf_conv_di.c\
	./src/conv/ft_printf_conv_pouxb.c\
	./src/conv/ft_printf_conv_f.c\
	./src/ft_printf.c\

NOM = $(basename $(SRC))

OBJ = ft_printf_handlers.o\
	ft_printf_color.o\
	ft_printf_parser.o\
	ft_printf_utility.o\
	ft_printf_buff_utility.o\
	ft_printf_conv_generic.o\
	ft_printf_conv_scpercent.o\
	ft_printf_conv_di.o\
	ft_printf_conv_pouxb.o\
	ft_printf_conv_f.o\
	ft_printf.o\

OBJLIB = ./libft/ft_getnbr.o\
	./libft/ft_isdigit.o\
	./libft/ft_isspace.o\
	./libft/ft_nbrlen.o\
	./libft/ft_strcmp.o\
	./libft/ft_strlen.o\
	./libft/ft_wcharlen.o\
	./libft/ft_wstrlen.o\
	./libft/ft_strncmp.o\

all: $(NAME)

$(NAME): $(SRC) ./include/ft_printf.h
	@make -C ./libft/
	@gcc $(FLAGS) -I ./include -I ./libft -c $(SRC)
	@ar rc $(NAME) $(OBJ) $(OBJLIB)
	@ranlib $(NAME)
	@echo "\033[1;34mft_printf\t\033[1;33mCompilation\t\033[0;32m[OK]\033[0m"

clean:
	@make -C ./libft clean
	@rm -rf $(OBJ)
	@echo "\033[1;34mft_printf\t\033[1;33mCleaning obj\t\033[0;32m[OK]\033[0m"

fclean: clean
	@make -C ./libft fclean
	@rm -rf $(NAME)
	@echo "\033[1;34mft_printf\t\033[1;33mCleaning lib\t\033[0;32m[OK]\033[0m"

re: fclean all
