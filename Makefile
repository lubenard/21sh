# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lubenard <lubenard@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/11/06 17:01:46 by lubenard          #+#    #+#              #
#    Updated: 2019/08/02 11:29:12 by lubenard         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = 21sh

SRC = srcs/main.c \
	  srcs/get_env.c \
	  srcs/handle_signals.c \
	  srcs/save_command.c \
	  srcs/free.c \
	  srcs/get_path.c \
	  srcs/builtins/setenv.c \
	  srcs/builtins/exit.c \
	  srcs/builtins/unsetenv.c \
	  srcs/builtins/env/env.c \
	  srcs/builtins/echo.c \
	  srcs/builtins/echo2.c \
	  srcs/builtins/cd.c \
	  srcs/builtins/cd2.c \
	  srcs/redirections/redirections.c \
	  srcs/redirections/left_redir.c \
	  srcs/redirections/right_redir.c \
	  srcs/redirections/parsing_redir.c \
	  srcs/redirections/ft_strsplit_redir.c \
	  srcs/pipe/pipe.c \
	  srcs/display/display_builtins.c \
	  srcs/display/display.c \
	  srcs/utils/find_lkd_lst.c \
	  srcs/parser/parser.c \
	  srcs/exec/execute_command.c \
	  srcs/exec/find_path.c \
	  srcs/input/line_edition.c \
	  srcs/input/term_mode.c \
	  srcs/input/get_cursor_pos.c \
	  srcs/input/move_cursor.c \
	  srcs/input/go_last_char.c \
	  srcs/input/right_arrow.c \
	  srcs/input/insert_del.c \
	  srcs/input/move_toword.c \
	  srcs/input/manage_quotes.c \
	  srcs/input/move_hist.c

INCLUDE_SRC = ./include/

OBJ = $(SRC:.c=.o)

CC = clang

CFLAGS = -Wall -Wextra -Werror -g3

all:  $(NAME)

$(NAME): $(OBJ)
	@cd libft && make
	@$(CC) -o $(NAME) $(CFLAGS) $(OBJ) -ltermcap libft/libft.a
	@printf "\033[33mCompilation de $(NAME)...\033[0m"
	@printf "\033[32m[✓]\033[0m\n"

libft:
	@cd libft && make

relib:
	@cd libft && make
	@$(CC) -o $(NAME) $(CFLAGS) $(OBJ) -ltermcap libft/libft.a
	@printf "\033[33mCompilation de $(NAME)...\033[0m"
	@printf "\033[32m[✓]\033[0m\n"

%.o : %.c
	@printf "\033[36mCompilation de $<...\033[0m"
	@$(CC) -c $(CFLAGS) -I$(INCLUDE_SRC) $< -o $@
	@printf "\033[32m[✓]\033[0m\n"

clean:
	@cd libft && make clean
	@rm -f $(OBJ)
	@printf "\033[31mclean de $(NAME)...\033[0m"
	@printf "\033[32m[✓]\033[0m\n"
	@rm -rf .history
	@rm -rf 21sh.dSYM

fclean: clean
	@rm -f $(NAME)
	@rm -f libft/libft.a
	@printf "\033[31mFclean de srcs/libft.a...\033[0m\033[32m[✓]\033[0m\n"
	@printf "\033[31mFclean de $(NAME)...\033[0m"
	@printf "\033[32m[✓]\033[0m\n"

re: fclean all

.SILENT:

.PHONY: all re fclean clean libft
