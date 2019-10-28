/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unsetenv.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/21 12:05:25 by lubenard          #+#    #+#             */
/*   Updated: 2019/10/28 14:30:29 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh21.h>

int			move_elements(t_env *lkd_env)
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
	return (2);
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
		return (move_elements(lkd_env));
	if (lkd_env->next)
		lkd_env->next->prev = lkd_env->prev;
	else
		lkd_env->next = NULL;
	return (0);
}

int			unset_env3(t_env *lkd_env, char *to_remove)
{
	char	*to_extract;
	int		ret;

	while (lkd_env)
	{
		to_extract = extract_first(lkd_env->env_line, '=');
		if (ft_strcmp(to_extract, to_remove) == 0)
		{
			ret = unset_env2(lkd_env, to_extract, to_remove);
			if (ret == 1)
				return (1);
			else if (ret != 2)
				free(lkd_env);
			free(to_extract);
			break ;
		}
		free(to_extract);
		lkd_env = lkd_env->next;
	}
	return (0);
}

int			unset_env(t_hustru *big_struc, char **command)
{
	t_env	*lkd_env;
	char	*to_remove;
	int		i;

	lkd_env = big_struc->lkd_env;
	if (verify_command(command, 1, &i))
		return (1);
	while (command[i])
	{
		to_remove = extract_first(command[i], '=');
		if (unset_env3(lkd_env, to_remove) == 1)
			return (error_setenv(NULL, 1));
		free(to_remove);
		i++;
	}
	if (big_struc->path)
		ft_deltab(&big_struc->path);
	big_struc->path = get_path(find_in_env(big_struc->lkd_env,
		ft_strdup("PATH")));
	return (0);
}
