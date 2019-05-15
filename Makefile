# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lubenard <lubenard@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/11/06 17:01:46 by lubenard          #+#    #+#              #
#    Updated: 2019/05/15 17:11:17 by lubenard         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = 21sh

SRC = srcs/main.c \
	  srcs/display.c \
	  srcs/get_env.c \
	  builtins/printf_env.c \
	  builtins/setenv.c \
	  builtins/unsetenv.c \
	  builtins/print_env.c \
	  builtins/display_builtins.c

OBJ = $(SRC:.c=.o)

CC = clang

CFLAGS = -Wall -Wextra -Werror -g3

all:  $(NAME)

$(NAME): $(OBJ)
	@cd libft && make
	@$(CC) -o $(NAME) $(CFLAGS) $(OBJ) libft/libft.a
	@printf "\033[33mCompilation de $(NAME)...\033[0m"
	@printf "\033[32m[✓]\033[0m\n"

libft:
	@cd libft && make

%.o : %.c
	@printf "\033[36mCompilation de $<...\033[0m"
	@$(CC) -c $(CFLAGS) $< -o $@
	@printf "\033[32m[✓]\033[0m\n"

clean:
	@cd libft && make clean
	@rm -f $(OBJ)
	@printf "\033[31mclean de $(NAME)...\033[0m"
	@printf "\033[32m[✓]\033[0m\n"

fclean: clean
	@rm -f $(NAME)
	@rm -f libft/libft.a
	@printf "\033[31mFclean de srcs/libft.a...\033[0m\033[32m[✓]\033[0m\n"
	@printf "\033[31mFclean de $(NAME)...\033[0m"
	@printf "\033[32m[✓]\033[0m\n"
	@rm -rf .history

re: fclean all

.SILENT:

.PHONY: all re fclean clean libft
