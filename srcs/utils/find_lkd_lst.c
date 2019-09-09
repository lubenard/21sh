/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_lkd_lst.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/16 15:56:10 by lubenard          #+#    #+#             */
/*   Updated: 2019/09/09 17:47:48 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh21.h>

char	*extract_first(char *command, char stop)
{
	int		i;

	i = 0;
	while (command[i] != stop && command[i])
		++i;
	return (ft_strsub(command, 0, i));
}

char	*extract_last(char *command, char last)
{
	int		i;
	int		e;

	i = 0;
	e = 0;
	while (command[i] && command[i] != last)
		i++;
	while (command[i] == last)
		i++;
	while (command[i + e])
		e++;
	return (ft_strsub(command, i, e));
}

char	*find_in_env(t_env *lkd_env, char *to_find)
{
	int		i;
	int		e;
	char	*occur;

	i = 0;
	e = 0;
	while (lkd_env)
	{
		occur = extract_first(lkd_env->env_line, '=');
		if (!ft_strcmp(occur, to_find))
		{
			while (lkd_env->env_line[i] && lkd_env->env_line[i] != '=')
				i++;
			i++;
			while (lkd_env->env_line[i + e])
				e++;
			free(to_find);
			free(occur);
			return (ft_strsub(lkd_env->env_line, i, e));
		}
		free(occur);
		lkd_env = lkd_env->next;
	}
	free(to_find);
	return (NULL);
}
