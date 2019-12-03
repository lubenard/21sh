/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/22 14:06:51 by lubenard          #+#    #+#             */
/*   Updated: 2019/12/03 00:34:21 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

# include "../libft/libft.h"
# include "struc.h"

# define PE_I 1
# define PE_V 2
# define PE_0 4

/*
** Env functions
*/

t_env	*ft_envcpy(t_env *start);
int		parsing_env(t_hustru *big_struc, char **command);
t_env	*parse_env(t_hustru *big_struc, char **command,
	int flags, int *is_command);
int		launch_command_env(t_hustru *big_struc, int flags, char **command);
void	fill_env(t_env *lkd_env, char **command, int i);
char	**compact_argv_env(char **env, int i);
int		exec_env(char *right_path, char **argv, char **tab_env);

/*
** Env display functions
*/
int		print_env(t_hustru *big_struc, char **command);
t_env	*print_env_no_command(t_env *env, int flags, int *is_command);
void	print_verbose_env(t_env *env, char **argv, int mode);
int		print_error_env(char option, int mode);
int		print_basic_env(t_env *lkd_env, int flags, int mode);
t_env	*print_env_and_var(t_env *lkd_env, int flags,
	int *is_command);
void	verbose(t_env *env, char *right_path, char *command);
/*
** External command
*/
t_env	*new_maillon_env();
char	*find_in_env(t_env *lkd_env, char *to_find);
char	*extract_first(char *command, char stop);
char	*find_path(char **path, char *first_command);
char	**compact_env(t_env *lkd_env);
int		set_env2(t_env **lkd_env, char *to_search, char *to_add);
void	free_env(t_env *env);

#endif
