/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh21.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymarcill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/15 15:03:32 by ymarcill          #+#    #+#             */
/*   Updated: 2019/06/12 16:47:43 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SH21_H
# define SH21_H

# include "../libft/libft.h"
# include <sys/wait.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/ioctl.h>
# include <unistd.h>
# include <dirent.h>
# include <signal.h>
# include <limits.h>

#include <stdio.h>

# define PE_I 1
# define PE_V 2
# define PE_0 4

typedef struct		s_env
{
	char			env_line[4096];
	struct s_env	*prev;
	struct s_env	*next;
}					t_env;

typedef struct		s_hist
{
	char			history[131073];
	struct s_hist	*prev;
	struct s_hist	*next;
}					t_hist;

/*
** Display / error functions
*/
void				display_prompt(char *username, char *curr_dir);
char				*error_setenv(char *command, int i, int e);
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
void				set_env(t_env *lkd_env, char *command);
void				unset_env(t_env *lkd_env, char *command);
int					print_env(t_env *lkd_env, char *command, char **path);
void				history(t_hist *lkd_hist);
int					find_exit(char *command);
int					ft_exit(int nbr);
/*
** Redirections
*/
void				redirections(t_env *lkd_env, char **path, char *command);
void				save_redir(char *command, char *content);
/*
** Pipe
*/
int					handle_pipe(t_env *lkd_env, char **path, char *command);
/*
** Handle Signal
*/
void				handle_signals(int sig);
void				handle_signals_proc(int sig);
/*
** History
*/
void				save_command(t_hist **lkd_hist, char *command);
/*
** Execution of command
*/
int					execute_command(char *get_right_path,
	char *command, char **argv, char **env);
int		exec_command_gen(char *path, char **argv, char **env);
/*
** Other
*/
char				*extract_params(char *command);
char				*extract_first_env(char *command, int mode);
char				*find_in_env(t_env *lkd_env, char *to_find);
int					free_after_exec(char *get_right_path,
	char **argv, char **env);
int					get_error_exec(char path[6000], int mode);
char				**compact_env(t_env *lkd_env);
char				**ft_strsplit_redir(char const *s, char c);
char				*find_path(char **path, char *first_command);
char				**get_path(char *path_line);

#endif
