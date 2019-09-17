/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setenv.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/20 18:57:20 by lubenard          #+#    #+#             */
/*   Updated: 2019/09/17 12:56:59 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh21.h>

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
			free(to_search);
			return (1);
		}
		*lkd_env = (*lkd_env)->next;
		free(to_extract);
	}
	return (0);
}

void	set_env3(t_env **lkd_env, char *to_search,
	char *to_extract, char *command)
{
	to_extract = extract_first((*lkd_env)->env_line, '=');
	if (ft_strcmp(to_search, to_extract) == 0)
	{
		ft_strcpy((*lkd_env)->env_line, command);
		free(to_search);
	}
	else
		create_new((*lkd_env), to_search, command);
	free(to_extract);
}

int		verify_command(char **command)
{
	if (!command[1])
	{
		ft_putendl_fd("setenv: no argument detected", 2);
		ft_putendl_fd("Usage: setenv VAR1=value1 VAR2=value2 ...", 2);
		return (1);
	}
	return (0);
}

int		set_env(t_hustru *big_struc, char **command)
{
	char	*to_search;
	char	*to_extract;
	t_env	*lkd_env;
	int		i;

	i = 1;
	to_extract = NULL;
	lkd_env = big_struc->lkd_env;
	if (verify_command(command))
		return (1);
	while (command[i])
	{
		if (ft_strchr(command[i], '=') == 0
		|| !(to_search = extract_first(command[i], '=')))
			return (1);
		to_search = ft_strupper(to_search);
		if (set_env2(&lkd_env, to_search, to_extract, command[i]) == 0)
			set_env3(&lkd_env, to_search, to_extract,command[i]);
		i++;
	}
	if (big_struc->path)
		ft_deltab(big_struc->path);
	big_struc->path = get_path(find_in_env(big_struc->lkd_env,
		ft_strdup("PATH")));
	return (0);
}
