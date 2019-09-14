/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/22 13:37:44 by lubenard          #+#    #+#             */
/*   Updated: 2019/09/14 12:10:59 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <env.h>

int		env_available_option(char *tab, int *flags)
{
	int i;

	while (*(++tab))
	{
		if (!(i = ft_strchri("iv0", tab[0])))
		{
			print_error_env(tab[0], 0);
			return (0);
		}
		*flags |= (1 << (i - 1));
	}
	if (*flags & PE_V && *flags & PE_I)
		print_verbose_env(NULL, NULL, 0);
	return (i);
}

int		parsing_env(t_hustru *big_struc, char **command)
{
	int		flags;
	int		i;

	flags = 0;
	i = 1;
	if (!ft_strcmp(command[1], "--help"))
		return (print_error_env('c', 1));
	while (command[i] && command[i][0] == '-')
	{
		if (!env_available_option(command[i], &flags) || !command[i][1])
			return (0);
		i++;
	}
	return (launch_command_env(big_struc, flags, command));
}

t_env	*parse_env(t_env *lkd_env, char **command, int flags, int *is_command)
{
	int		i;
	size_t	k;
	t_env	*env;

	i = 1;
	env = new_maillon_env();
	while (command[i] && ft_strchr(command[i], '-'))
		i++;
	while (command[i] && (k = ft_strchri(command[i], '=')) && k != 1)
		fill_env(env, command, i++);
	if (!command[i] && flags & PE_I)
		return (print_env_no_command(env, flags, is_command));
	else if (!(flags & PE_I) && !command[i])
		return (print_env_and_var(lkd_env, env, flags, is_command));
	if (env->env_line[0] != '\0')
		return (env);
	free(env);
	return (NULL);
}
