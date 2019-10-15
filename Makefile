# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lubenard <lubenard@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/11/06 17:01:46 by lubenard          #+#    #+#              #
#    Updated: 2019/10/15 15:06:26 by lubenard         ###   ########.fr        #
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
	  srcs/builtins/echo.c \
	  srcs/builtins/echo2.c \
	  srcs/builtins/cd.c \
	  srcs/builtins/env/env.c \
	  srcs/builtins/env/display_env.c \
	  srcs/builtins/env/display_env2.c \
	  srcs/builtins/env/parsing_env.c \
	  srcs/redirections/redirections.c \
	  srcs/redirections/launch_redir.c \
	  srcs/redirections/parsing_redir.c \
	  srcs/redirections/parse_redir.c \
	  srcs/redirections/heredoc.c \
	  srcs/pipe/pipe.c \
	  srcs/pipe/parse_pipe.c \
	  srcs/display/display_builtins.c \
	  srcs/display/display.c \
	  srcs/utils/find_lkd_lst.c \
	  srcs/parser/parser.c \
	  srcs/parser/lexer.c \
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
	  srcs/input/move_hist.c \
	  srcs/input/ft_copy_cut_paste_del.c \
	  srcs/input/signals.c \
	  srcs/input/char_handler.c \
	  srcs/input/tools.c \
	  srcs/input/manage_quotesbis.c \
	  srcs/input/tools_bis.c \
	  srcs/input/ft_read_char.c

INCLUDE_SRC = ./include/

OBJ = $(SRC:.c=.o)

CC = clang

CFLAGS = -Wall -Wextra -Werror -g3 #-fsanitize=address

all:  $(NAME)

$(NAME): $(OBJ)
	@make -j4 -C libft
	@$(CC) -o $(NAME) $(CFLAGS) $(OBJ) -ltermcap libft/libft.a
	@printf "\033[33mCompilation de $(NAME)...\033[0m"
	@printf "\033[32m[✓]\033[0m\n"

libft:
	@make -j4 -C libft

%.o : %.c
	@printf "\033[36mCompilation de $<...\033[0m"
	@$(CC) -c $(CFLAGS) -I$(INCLUDE_SRC) $< -o $@
	@printf "\033[32m[✓]\033[0m\n"

clean:
	@cd libft && make clean
	@rm -f $(OBJ)
	@printf "\033[31mSuppression des objets de $(NAME)...\033[0m"
	@printf "\033[32m[✓]\033[0m\n"
	@rm -rf .history
	@rm -rf 21sh.dSYM
	@rm -rf vgcore.*
	@rm -f file*

fclean: clean
	@printf "\033[31mSuppression de srcs/libft.a...\033[0m"
	@rm -rf srcs/libft.a
	@printf "\033[32m[✓]\033[0m\n"
	@printf "\033[31mSuppression de $(NAME)...\033[0m"
	@rm -f $(NAME)
	@printf "\033[32m[✓]\033[0m\n"

re: fclean all

.SILENT:

.PHONY: all re fclean clean libft
