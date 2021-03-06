/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struc.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/08 13:21:09 by lubenard          #+#    #+#             */
/*   Updated: 2019/11/20 19:55:06 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUC_H
# define STRUC_H

# include "../libft/libft.h"
# include <termios.h>

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
	size_t			index;
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
	char			*line;
	int				fds_index;
	int				should_heredoc;
	char			*pipe_heredoc;
	char			*history_path;
	char			*home_env_var;
	struct termios	old_p;
}					t_hustru;

#endif
