/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struc.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/08 13:21:09 by lubenard          #+#    #+#             */
/*   Updated: 2019/10/15 21:22:56 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUC_H
# define STRUC_H

# include "../libft/libft.h"

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
	char			*line;
	int				fds_index;
	char			*history_path;
}					t_hustru;

#endif
