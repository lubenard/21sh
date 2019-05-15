/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SH21.H                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymarcill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/15 15:03:32 by ymarcill          #+#    #+#             */
/*   Updated: 2019/05/15 17:13:41 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SH21_H
# define SH21_H

# include "../libft/libft.h"
# include <sys/wait.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <unistd.h>
# include <dirent.h>
# include <signal.h>

typedef struct		s_env
{
	char			env_line[4096];
	struct s_env	*prev;
	struct s_env	*next;
}					t_env;

typedef struct		s_history
{
	char			history[131072];
	struct s_env	*prev;
	struct s_env	*next;
}					t_history;
/*
** Display / error functions
*/
void				display_prompt(char *username, char *curr_dir);
char				*error_setenv(char *command, int i, int e);
/*
** Linked list
*/
t_env				*get_env(char **env);
t_env				*new_maillon(void);
/*
** Builtins
*/
void				set_env(t_env *lkd_env, char *command);
void				unset_env(t_env *lkd_env, char *command);
void				print_env(t_env *lkd_env);
/*
** Other
*/
char				*extract_params(char *command);
#endif
