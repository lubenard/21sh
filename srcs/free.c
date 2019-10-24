/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/03 17:01:28 by lubenard          #+#    #+#             */
/*   Updated: 2019/10/24 17:22:14 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh21.h>

/*
** Free after each exec
*/

int		free_after_exec(char *get_right_path, char **env)
{
	free(get_right_path);
	free(env);
	return (0);
}

/*
** Free env linked list
*/

void	free_env(t_env *env)
{
	t_env	*tmp;

	while (env)
	{
		tmp = env;
		env = env->next;
		//if (tmp)
		//{
			free(tmp);
			//tmp = NULL;
		//}
	}
}

/*
** free after exiting the shell
*/

void	free_after_exit(t_env *lkd_env, t_hist *lkd_hist, char **path)
{
	t_hist	*tmp2;

	free_env(lkd_env);
	while (lkd_hist)
	{
		tmp2 = lkd_hist;
		lkd_hist = lkd_hist->prev;
		free(tmp2);
		//tmp2 = NULL;
	}
	if (path != NULL)
		ft_deltab(&path);
}
