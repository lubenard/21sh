/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/04 14:09:48 by lubenard          #+#    #+#             */
/*   Updated: 2019/10/21 23:07:59 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <env.h>

void	fill_env(t_env *env, char **command, int i)
{
	t_env	*new_element;
	char	*fie;

	if ((fie = find_in_env(env, extract_first(command[i], '='))))
		fill_env2(env, command, i);
	else
	{
		if (ft_strcmp(env->env_line, ""))
		{
			while (env->next)
				env = env->next;
			new_element = new_maillon_env();
			ft_strcpy(new_element->env_line, command[i]);
			env->next = new_element;
			env = new_element;
		}
		else
			ft_strcpy(env->env_line, command[i]);
	}
	free(fie);
}

int		exec_file_env(t_env *env, char **command,
	t_hustru *big_struc, int flags)
{
	char	**tab_env;
	char	*right_path;
	char	**argv;
	int		i;

	i = 1;
	while (command[i][0] == '-' || ft_strchr(command[i], '='))
		i++;
	right_path = find_path(big_struc->path, command[i]);
	if (flags & PE_V)
		verbose(env, right_path, command[i]);
	argv = compact_argv_env(command, i);
	if (flags & PE_V)
		print_verbose_env(NULL, argv, 2);
	if (right_path == NULL)
	{
		ft_putstr("No file found with the following name: ");
		ft_putendl(command[i]);
		free_env(env);
		return (127);
	}
	tab_env = compact_env(env);
	ft_deltab(&argv);
	exec_command_gen(right_path, argv, tab_env);
	return (0);
}

int		exec_custom_env(t_env *env, char **command,
	t_hustru *big_struc, int flags)
{
	t_env	*lkd_env;
	int		ret;
	int		save;
	int		i;

	save = 0;
	i = 0;
	lkd_env = big_struc->lkd_env;
	while (lkd_env->next)
	{
		lkd_env = lkd_env->next;
		save++;
	}
	lkd_env->next = env;
	ret = (flags & PE_I) ? exec_file_env(env, command, big_struc, flags) :
	exec_file_env(big_struc->lkd_env, command, big_struc, flags);
	lkd_env = big_struc->lkd_env;
	while (i != save)
	{
		lkd_env = lkd_env->next;
		i++;
	}
	lkd_env->next = NULL;
	return (ret);
}

int		launch_command_env(t_hustru *big_struc, int flags,
	char **command)
{
	t_env	*env;
	int		is_command;
	t_env	*lkd_env;

	lkd_env = big_struc->lkd_env;
	is_command = 1;
	env = parse_env(lkd_env, command, flags, &is_command);
	if (is_command == 1 && (flags & PE_I || ft_tabchr(command, '=')))
		exec_custom_env(env, command, big_struc, flags);
	else if (is_command == 1)
		return (exec_file_env(big_struc->lkd_env, command, big_struc, flags));
	free_env(env);
	return (0);
}

int		print_env(t_hustru *big_struc, char **command)
{
	if (!command[1])
		return (print_basic_env(big_struc->lkd_env, 0, 0));
	else
		return (parsing_env(big_struc, command));
}
