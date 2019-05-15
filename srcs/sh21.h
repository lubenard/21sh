/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SH21.H                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymarcill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/15 15:03:32 by ymarcill          #+#    #+#             */
/*   Updated: 2019/05/15 16:13:30 by lubenard         ###   ########.fr       */
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
	char			env_line[131072];
	struct s_env	*prev;
	struct s_env	*next;
}					t_env;

typedef struct		s_history
{
	char			history[131072];
	struct s_env	*prev;
	struct s_env	*next;
}					t_history;

void				display_prompt();
t_env				*get_env(char **env);

#endif
