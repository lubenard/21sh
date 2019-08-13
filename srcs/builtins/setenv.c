/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setenv.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/20 18:57:20 by lubenard          #+#    #+#             */
/*   Updated: 2019/08/13 18:08:42 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh21.h>

char	*extract_first_env(char *command)
{
	int		i;
	int		e;

	i = 0;
	e = 0;
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

int		create_new(t_env *lkd_env, char *to_search, char *to_add)
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
	return (0);
}

int		set_env2(t_env **lkd_env, char *to_search,
	char *to_extract, char *to_add)
{
	while ((*lkd_env)->next)
	{
		to_extract = extract_first((*lkd_env)->env_line, '=');
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

int		set_env(t_hustru *big_struc, char *command)
{
	char	*to_add;
	char	*to_search;
	char	*to_extract;
	int		ret;
	t_env	*lkd_env;

	lkd_env = big_struc->lkd_env;
	to_extract = NULL;
	ret = 0;
	if (ft_strchr(command, '=') == 0
	|| !(to_search = extract_first_env(command)))
		return (1);
	to_add = extract_params(command);
	to_search = ft_strupper(to_search);
	if (set_env2(&lkd_env, to_search, to_extract, to_add) == 0)
	{
		to_extract = extract_first(lkd_env->env_line, '=');
		if (ft_strcmp(to_search, to_extract) == 0)
		{
			ft_strcpy(lkd_env->env_line, to_add);
			free(to_search);
			free(to_add);
		}
		else
			ret = create_new(lkd_env, to_search, to_add);
		free(to_extract);
	}
	big_struc->path = get_path(find_in_env(big_struc->lkd_env, ft_strdup("PATH")));
	return (ret);
}
