/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh21.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymarcill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/15 15:03:32 by ymarcill          #+#    #+#             */
/*   Updated: 2019/10/08 01:22:29 by lubenard         ###   ########.fr       */
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
#include <stdio.h>

/*
** Line Edition
*/
int		set_none_canon_mode(int fd);
int		reset_shell_attr(int fd);
/*
** Display / error functions
*/
int		verify_command(char **command, int i);
void	display_prompt(char *username, char *curr_dir);
int		error_setenv(int i);
char	*error_echo(char user[4096]);
int		invalid_command(char *command);
char	*find_name(t_env *lkd_env);
char	*find_cur_dir(t_env *lkd_env);
int		print_shell_help(void);
int		display_error(char *error, char *command);
/*
** Linked list env
*/
t_env	*get_env(char **env);
t_env	*new_maillon_env(void);
/*
** Linked list history
*/
t_hist	*new_maillon_hist(void);
/*
** Builtins
*/
int		set_env(t_hustru *big_struc, char **command);
int		unset_env(t_hustru *big_struc, char **command);
int		print_env(t_hustru *big_struc, char **command);
int		history(t_hist *lkd_hist);
int		find_exit(t_hustru *big_struc, char **command);
int		ft_exit(t_hustru *big_struc, int nbr);
int		ft_echo(t_hustru *big_struc, char **command);
int		cd(t_hustru *big_struc, char **commmand);
/*
** Redirections
*/
int		redirections(t_hustru *big_struc, char *command);
/*
** Pipe
*/
int		handle_pipe(t_hustru *big_struc, char *command);
/*
** Parser
*/
int		parser(t_hustru *big_struc, char *command);
/*
** Handle Signal
*/
void	handle_signals_proc(int sig);
/*
** History
*/
void	save_command(t_hustru *big_struc, char *command, int save);
char	*get_quotes(char *line, t_hustru *big_struc);
/*
** Execution of command
*/
int		exec_command_gen(t_hustru *big_struc, char **argv);
int		exec_without_fork(t_hustru *big_struc, char **argv);
/*
**
*/
char	*autocomplete(t_hustru *big_struc, char *command);
/*
** Other
*/
char	*extract_first_env(char *command);
char	*extract_last(char *command, char start);
char	*find_in_env(t_env *lkd_env, char *to_find);
int		free_after_exec(char *get_right_path, char **env);
int		get_error_exec(char path[6000]);
char	**compact_env(t_env *lkd_env);
char	*find_path(char **path, char *first_command);
char	**get_path(char *path_line);
void	free_after_exit(t_env *lkd_env, t_hist *lkd_hist, char **path);
char	*extract_path(char *command);
char	*extract_first(char *command, char stop);
int		basic_command(t_hustru *big_struc, char **command,
		int (*fun)(t_hustru *, char **));
int		decide_commande(t_hustru *big_struc, char **command,
		int (*fun)(t_hustru *, char **));
void	handle_echo_options(char option);
/*
** Redirections utils
*/
char	*heredoc(t_hustru *big_struc, char **tab_line);
int		extract_first_fd(char **command, int i, char *to_convert);
char	**parse_redir(char *str);
char	**create_command(char **command, int i);
int		count_elem_redir(char **tab, int i);
int		launch_arrow(t_hustru *big_struc, char **command);
int		print_error_redirect(char *code);
int		create_file(char **filenames, int i);
/*
** Pipe utils
*/
void	close_pipe(int *pipes, int i);
char	***compact_command(char *command);
int		free_pipe(char ***command);

/*
** Buitltins Utils
*/
char	*handle_dollar(t_hustru *big_struc, char *command);
char	*handle_tilde(t_hustru *big_struc, char *command);

#endif
