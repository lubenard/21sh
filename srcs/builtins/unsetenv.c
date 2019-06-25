/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unsetenv.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/21 12:05:25 by lubenard          #+#    #+#             */
/*   Updated: 2019/06/25 13:40:36 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh21.h>

char		*extract_params(char *command)
{
	int		i;
	int		e;

	i = 0;
	e = 0;
	while (command[i] && command[i] != ' ')
		++i;
	while (command[i] == ' ' || command[i] == '\t')
		++i;
	while (command[i + e])
		++e;
	return (ft_strsub(command, i, e));
}

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

int			unset_env(t_hustru *big_struc, char *command)
{
	char	*to_extract;
	int		i;
	char	*to_remove;

	to_remove = (ft_strchr(command, '=')) ? extract_params(command)
		: extract_first_env(command);
	while (to_remove && big_struc->lkd_env)
	{
		i = 0;
		while (big_struc->lkd_env->env_line[i] != '=')
			++i;
		to_extract = ft_strsub(big_struc->lkd_env->env_line, 0, i);
		if (ft_strcmp(to_extract, to_remove) == 0)
		{
			if (unset_env2(big_struc->lkd_env, to_extract, to_remove) == 1)
				return (1);
			free(to_extract);
			free(big_struc->lkd_env);
			break ;
		}
		free(to_extract);
		big_struc->lkd_env = big_struc->lkd_env->next;
	}
	free(to_remove);
	return (0);
}
