/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unsetenv.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/21 12:05:25 by lubenard          #+#    #+#             */
/*   Updated: 2019/08/17 00:26:58 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh21.h>

int			move_elements(t_env *lkd_env, char *to_extract, char *to_remove)
{
	while (lkd_env->next)
	{
		if (ft_strcmp(lkd_env->next->env_line, ""))
		{
			ft_strcpy(lkd_env->env_line, lkd_env->next->env_line);
			lkd_env = lkd_env->next;
		}
		else
			break ;
	}
	lkd_env->prev->next = NULL;
	free(lkd_env);
	free(to_extract);
	free(to_remove);
	return (1);
}

int			unset_env2(t_env *lkd_env, char *to_extract, char *to_remove)
{
	if (!lkd_env->prev && !lkd_env->next)
	{
		ft_bzero(lkd_env->env_line, 2056);
		free(to_extract);
		free(to_remove);
		return (1);
	}
	if (lkd_env->prev)
		lkd_env->prev->next = lkd_env->next;
	else
		return (move_elements(lkd_env, to_extract, to_remove));
	if (lkd_env->next)
		lkd_env->next->prev = lkd_env->prev;
	else
		lkd_env->next = NULL;
	return (0);
}

int			unset_env(t_hustru *big_struc, char **command)
{
	char	*to_extract;
	char	*to_remove;
	t_env	*lkd_env;

	lkd_env = big_struc->lkd_env;
	to_remove = (ft_tabchr(command, '=')) ? extract_first(command[1], '=')
		: extract_first(command[1], ' ');
	while (to_remove && lkd_env)
	{
		to_extract = extract_first(lkd_env->env_line, '=');
		if (ft_strcmp(to_extract, to_remove) == 0)
		{
			if (unset_env2(lkd_env, to_extract, to_remove) == 1)
				return (1);
			free(to_extract);
			free(lkd_env);
			break ;
		}
		free(to_extract);
		lkd_env = lkd_env->next;
	}
	free(to_remove);
	ft_deltab(big_struc->path);
	big_struc->path = get_path(find_in_env(big_struc->lkd_env, ft_strdup("PATH")));
	return (0);
}
