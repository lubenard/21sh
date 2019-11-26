/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/03 17:01:28 by lubenard          #+#    #+#             */
/*   Updated: 2019/11/26 17:39:16 by ymarcill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh21.h>

/*
** Free after each exec
*/

int		free_after_exec(char *get_right_path, char **env, int ret)
{
	free(get_right_path);
	free(env);
	if (ret > 255)
		return (ret - 255);
	return (ret);
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
		free(tmp);
	}
}

void	free_env_prev(t_env *env)
{
	t_env	*tmp;

	while (env)
	{
		tmp = env;
		env = env->next;
		free(tmp);
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
	}
	if (path != NULL)
		ft_deltab(&path);
}
