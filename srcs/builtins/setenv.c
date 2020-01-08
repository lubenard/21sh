/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setenv.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/20 18:57:20 by lubenard          #+#    #+#             */
/*   Updated: 2020/01/08 15:16:24 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh21.h>

/*
** Create new element, then add the new element to the linked list
** The new element contains the new environ variable
*/

int		create_new(t_env *lkd_env, char *to_search, char *to_add)
{
	t_env *new_element;

	if (!lkd_env->next && !lkd_env->prev
	&& !ft_strcmp(lkd_env->env_line, ""))
		ft_strlcpy(lkd_env->env_line, to_add, 4095);
	else
	{
		new_element = new_maillon_env();
		lkd_env->next = new_element;
		lkd_env->next->prev = lkd_env;
		ft_strlcpy(new_element->env_line, to_add, 4095);
	}
	ft_strdel(&to_search);
	return (0);
}

/*
** Search if the variable in env already exist, and if it does,
** replace it
*/

int		set_env2(t_env **lkd_env, char *to_search, char *to_add)
{
	char *to_extract;

	while ((*lkd_env)->next)
	{
		to_extract = extract_first((*lkd_env)->env_line, '=');
		if (ft_strcmp(to_search, to_extract) == 0)
		{
			ft_strcpy((*lkd_env)->env_line, to_add);
			ft_strdel(&to_extract);
			ft_strdel(&to_search);
			return (1);
		}
		*lkd_env = (*lkd_env)->next;
		ft_strdel(&to_extract);
	}
	return (0);
}

/*
** Decide if you need to create a new element
*/

void	set_env3(t_env **lkd_env, char *to_search, char *command)
{
	char *to_extract;

	to_extract = extract_first((*lkd_env)->env_line, '=');
	if (ft_strcmp(to_search, to_extract) == 0)
	{
		ft_strlcpy((*lkd_env)->env_line, command, 4095);
		ft_strdel(&to_search);
	}
	else
		create_new((*lkd_env), to_search, command);
	ft_strdel(&to_extract);
}

/*
** Check if there is at least 1 argument
*/

int		verify_command(char **command, int i, int *index)
{
	char	*tmp;

	*index = 1;
	if (!command[1])
	{
		if (i == 1)
			ft_putstr_fd("un", 2);
		ft_putendl_fd("setenv: no argument detected", 2);
		ft_putstr_fd("Usage: ", 2);
		if (i == 1)
			ft_putstr_fd("un", 2);
		ft_putendl_fd("setenv VAR1=value1 VAR2=value2 ...", 2);
		return (1);
	}
	tmp = extract_first(command[1], '=');
	if (ft_occur(tmp, ':'))
	{
		ft_putendl_fd("setenv : bad character in varname", 2);
		ft_strdel(&tmp);
		return (1);
	}
	ft_strdel(&tmp);
	return (0);
}

/*
** Check options and launch in consequence
** It does treats all args
*/

int		set_env(t_hustru *big_struc, char **command)
{
	char	*to_search;
	t_env	*lkd_env;
	int		i;

	to_search = NULL;
	lkd_env = big_struc->lkd_env;
	if (verify_command(command, 0, &i))
		return (1);
	while (command[i])
	{
		if (!ft_strchr(command[i], '=')
		|| !(to_search = extract_first(command[i], '='))
		|| !ft_strcmp(to_search, ""))
			return (error_setenv(to_search, 0));
		if (set_env2(&lkd_env, to_search, command[i]) == 0)
			set_env3(&lkd_env, to_search, command[i]);
		i++;
		to_search = NULL;
	}
	if (big_struc->path)
		ft_deltab(&big_struc->path);
	big_struc->path = get_path(find_in_env(big_struc->lkd_env,
		ft_strdup("PATH")));
	return (0);
}
