/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setenv.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/20 18:57:20 by lubenard          #+#    #+#             */
/*   Updated: 2019/06/07 11:15:59 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../sh21.h"

char	*extract_first_env(char *command, int mode)
{
	int		i;
	int		e;

	i = 0;
	e = 0;
	if (mode == 0)
	{
		while (command[i] != '=' && command[i])
			++i;
		return (ft_strsub(command, 0, i));
	}
	else
	{
		while (command[i] && command[i] != ' ')
			++i;
		while (command[i] == ' ' || command[i] == '\t')
			++i;
		while (command[i + e] && command[i + e] != '=')
			++e;
		if (e == 0)
			return (ft_strdup(command));
		return (error_setenv(command, i, e));
	}
}

void	create_new(t_env *lkd_env, char *to_search, char *to_add)
{
	t_env *new_element;

	if (!lkd_env->next && !lkd_env->prev
	&& !ft_strcmp(lkd_env->env_line, ""))
		ft_strcpy(lkd_env->env_line, to_add);
	else
	{
		new_element = new_maillon_env();
		lkd_env->next = new_element;
		lkd_env->next->prev = lkd_env;
		ft_strcpy(new_element->env_line, to_add);
	}
	free(to_search);
	free(to_add);
}

int		set_env2(t_env **lkd_env, char *to_search,
	char *to_extract, char *to_add)
{
	while ((*lkd_env)->next)
	{
		to_extract = extract_first_env((*lkd_env)->env_line, 0);
		if (ft_strcmp(to_search, to_extract) == 0)
		{
			ft_strcpy((*lkd_env)->env_line, to_add);
			free(to_extract);
			free(to_add);
			free(to_search);
			return (1);
		}
		*lkd_env = (*lkd_env)->next;
		free(to_extract);
	}
	return (0);
}

void	set_env(t_env *lkd_env, char *command)
{
	char	*to_add;
	char	*to_search;
	char	*to_extract;

	to_extract = NULL;
	if (ft_strchr(command, '=') == 0
	|| !(to_search = extract_first_env(command, 1)))
		return ;
	to_add = extract_params(command);
	to_search = ft_strupper(to_search);
	if (set_env2(&lkd_env, to_search, to_extract, to_add) == 0)
	{
		to_extract = extract_first_env(lkd_env->env_line, 0);
		if (ft_strcmp(to_search, to_extract) == 0)
		{
			ft_strcpy(lkd_env->env_line, to_add);
			free(to_search);
			free(to_add);
		}
		else
			create_new(lkd_env, to_search, to_add);
		free(to_extract);
	}
}
