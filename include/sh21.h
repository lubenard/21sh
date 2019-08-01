/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh21.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymarcill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/15 15:03:32 by ymarcill          #+#    #+#             */
/*   Updated: 2019/08/01 19:16:21 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SH21_H
# define SH21_H

# include "../libft/libft.h"
# include <sys/wait.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/ioctl.h>
# include <dirent.h>
# include <signal.h>
# include <limits.h>

#include <stdio.h>

# define PE_I 1
# define PE_V 2
# define PE_0 4

/*
** Env linked list
*/

typedef struct		s_env
{
	char			env_line[4096];
	struct s_env	*prev;
	struct s_env	*next;
}					t_env;

/*
** History linked list
*/

typedef struct		s_hist
{
	char			history[131073];
	struct s_hist	*prev;
	struct s_hist	*next;
}					t_hist;

/*
** Main structure conatining linked list
*/

typedef struct		s_hustru
{
	struct s_env	*lkd_env;
	struct s_hist	*lkd_hist;
	char			**path;
	int				last_ret;
}					t_hustru;

/*
** Display / error functions
*/
void				display_prompt(char *username, char *curr_dir);
char				*error_setenv(char *command, int i, int e);
void				error_echo(char user[33]);
void				invalid_command(char *command);
char				*find_name(t_env *lkd_env);
char				*find_cur_dir(t_env *lkd_env);
/*
** Linked list env
*/
t_env				*get_env(char **env);
t_env				*new_maillon_env(void);
/*
** Linked list history
*/
t_hist				*new_maillon_hist(void);
/*
** Builtins
*/
int					set_env(t_env *lkd_env, char *command);
int					unset_env(t_hustru *big_struc, char *command);
int					print_env(t_hustru *big_struc, char *command);
void				history(t_hist *lkd_hist);
int					find_exit(char *command, t_hustru *big_struc);
int					ft_exit(int nbr, t_hustru *big_struc);
int					ft_echo(t_hustru *big_struc, char *command);
int					cd(t_hustru *big_struc, char *commmand);
/*
** Redirections
*/
void				redirections(t_env *lkd_env, char **path, char *command);
void				redir_and_pipe(t_env *lkd_env, char **path, char *command);
void				save_redir(char *command, char *content);
/*
** Pipe
*/
int					handle_pipe(t_env *lkd_env, char **path, char *command);
/*
** Parser
*/
int					parser(t_hustru *big_struc, char *command);
/*
** Handle Signal
*/
void				handle_signals(int sig);
void				handle_signals_proc(int sig);
/*
** History
*/
char				*move_hist(char *buf, char *line, int **prompt, t_hustru *big_struc);
void				save_command(t_hustru *big_struc, char *command);
char				*get_quotes(char *line, t_hustru *big_struc);
/*
** Execution of command
*/
int					execute_command(char *get_right_path,
	char *command, char **argv, char **env);
int					exec_command_gen(char *path, char **argv, char **env);
/*
** Other
*/
char				*extract_params(char *command);
char				*extract_first_env(char *command);
char				*find_in_env(t_env *lkd_env, char *to_find);
int					free_after_exec(char *get_right_path,
	char **argv, char **env);
int					get_error_exec(char path[6000]);
char				**compact_env(t_env *lkd_env);
char				**ft_strsplit_redir(char const *s, char c);
char				*find_path(char **path, char *first_command);
char				**get_path(char *path_line);
void				free_after_exit(t_env *lkd_env,
	t_hist *lkd_hist, char **path);
int					handle_tilde2(t_env *lkd_env, int i);
char				*extract_path(char *command);
char				*extract_first(char *command, char stop);
/*
** Redirections utils
*/
void				ft_str_start_cat(char *dest, const char *src, int start);
int					count_elem_redir(char **tab, int i);
int					pass_filename(char **tab, int i);
void				arrow_right(t_env *lkd_env, char **path, char *command);
void				double_arrow_left(t_env *lkd_env, char *command);
void				simple_arrow_left(t_env *lkd_env, char *command);
int					print_error_redirect(char **tab, char *code);
char				**prepare_tab(char *command, char signe);

#endif
