/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh21.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymarcill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/15 15:03:32 by ymarcill          #+#    #+#             */
/*   Updated: 2019/11/21 14:13:56 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SH21_H
# define SH21_H

# include "struc.h"
# include <sys/wait.h>
# include <sys/stat.h>
# include <dirent.h>
# include <signal.h>
# include <limits.h>

/*
** Line Edition
*/
int				set_none_canon_mode(int fd);
int				reset_shell_attr(int fd);
/*
** Display / error functions
*/
int				verify_command(char **command, int i, int *index);
void			display_prompt(char *username, char *curr_dir);
int				error_setenv(char *to_search, int i);
char			*error_echo(char user[4096]);
int				invalid_command(char *command);
char			*find_name(t_env *lkd_env);
char			*find_cur_dir(t_env *lkd_env);
int				print_shell_help(void);
int				display_error(char *error, char *command);
int				print_error_redirect(char *code);
/*
** Linked list env
*/
t_env			*get_env(char **env);
t_env			*new_maillon_env(void);
/*
** Linked list history
*/
t_hist			*new_maillon_hist(void);
/*
** Builtins
*/
int				set_env(t_hustru *big_struc, char **command);
int				unset_env(t_hustru *big_struc, char **command);
int				print_env(t_hustru *big_struc, char **command);
int				history(t_hist *lkd_hist);
int				find_exit(t_hustru *big_struc, char **command);
int				ft_exit(t_hustru *big_struc, int nbr);
int				ft_echo(t_hustru *big_struc, char **command);
int				cd(t_hustru *big_struc, char **commmand);
/*
** Redirections
*/
int				redirections(t_hustru *big_struc, char **lexed_command,
				int should_fork);
/*
** Pipe
*/
int				handle_pipe(t_hustru *big_struc, char *command);
int				handle_pipe_w_fork(t_hustru *big_struc, char *command);
/*
** Parser
*/
int				parser(t_hustru *big_struc, char *command);
char			**main_lexer(char *line);
char			**lexer_redir(char *str);
char			**final_lexer(char *line);
int				check_error_lexer(char **tab_q);
int				check_semic_error(char **tab_q);
/*
** Handle Signal
*/
void			handle_signals_proc(int sig);
void			catch_signal(void);
/*
** History
*/
void			save_command(t_hustru *big_struc, char *command, int save);
char			*get_quotes(char *line, t_hustru *big_struc);
/*
** Execution of command
*/
int				exec_command_gen(t_hustru *big_struc, char **argv);
int				exec_without_fork(t_hustru *big_struc, char **argv);
/*
** Other
*/
char			*extract_first_env(char *command);
char			*extract_last(char *command, char start);
char			*find_in_env(t_env *lkd_env, char *to_find);
int				free_after_exec(char *get_right_path, char **env, int ret);
int				get_error_exec(char path[6000]);
char			**compact_env(t_env *lkd_env);
char			*find_path(char **path, char *first_command);
char			**get_path(char *path_line);
void			free_after_exit(t_env *lkd_env, t_hist *lkd_hist, char **path);
char			*extract_path(char *command);
char			*extract_first(char *command, char stop);
int				basic_command(t_hustru *big_struc, char **command,
	int (*fun)(t_hustru *, char **));
int				decide_commande(t_hustru *big_struc, char **command,
	int (*fun)(t_hustru *, char **), int should_fork);
char			**create_command(char **command, int *i, int *e);
int				is_valid_command(t_hustru *big_struc, char **argv);
int				is_between_quotes(char *command, int mode_quote);
char			**create_command(char **command, int *i, int *e);
int				is_between_quotes(char *command, int quote_mode);
int				is_between_quotes2(char **command, char quote_char);
void			remove_quote(char ***command);
void			swap_elem(char **command, char *replace);
void			change_env(t_hustru *big_struc);
t_hustru		*fill_huge_struc(t_env *lkd_env, t_hist *lkd_hist, char **path);
/*
** Redirections utils
*/
char			*heredoc(t_hustru *big_struc, char **tab_line);
int				extract_first_fd(char **command, int i, char *to_convert);
int				count_elem_redir(char **tab, int i);
int				launch_arrow(t_hustru *big_struc, char **command);
int				launch_arrow_w_fork(t_hustru *big_struc, char **command);
void			fd_redir(char **command, int *i);
int				file_redir(t_hustru *big_struc,
	char **command, int *i, int *fds);
int				init_arrays(char **command, int **fds,
				char ***exec_command, int *fds_size);
char			*recompact_command(char **command);
int				count_args_redir(char **tab, int i);
int				is_digit(char *str);
int				do_heredoc(t_hustru *big_struc, char **command);
/*
** Pipe utils
*/
void			close_pipe(int *pipes, int i);
char			***compact_command(char *command);
int				free_pipe(char ***command);
int				*prepare_pipe(t_hustru *big_struc, char ***compacted_command,
				char *command, int i);
char			*pipe_heredoc(t_hustru *big_struc, char ***command);
void			do_heredoc_pipe(t_hustru *big_struc, char ***tab, int j);
int				count_args_triple_tab(char ***tab);
/*
** Buitltins Utils
*/
char			*handle_dollar(t_hustru *big_struc, char *command);
char			*handle_tilde(t_hustru *big_struc, char *command);
char			*recompact_command_expansion(char **tab);
void			handle_tilde2(char user_name[4096], char *command, int i);

#endif
