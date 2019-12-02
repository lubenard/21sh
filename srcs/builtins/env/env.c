/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/04 14:09:48 by lubenard          #+#    #+#             */
/*   Updated: 2019/12/02 23:57:35 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <env.h>
#include <sh21.h>
# include <stdio.h>

void	fill_env(t_env *env, char **command, int i)
{
	t_env *new_element;

	char *to_search = extract_first(command[i], '=');
	if (env && find_in_env(env, ft_strdup(to_search)))
		set_env2(&env, to_search, command[i]);
	else
	{
		if (env)
		{
			new_element = new_maillon_env();
			ft_strcpy(new_element->env_line, command[i]);
			while (env->next)
				env = env->next;
			env->next = new_element;
			new_element->prev = env;
		}
		else
			ft_strcpy(env->env_line, command[i]);
	}
}

int		print_err_env(char **compacted_env, char *comm)
{
	ft_putstr_fd("No file found with the following name: ", 2);
	ft_putendl_fd(comm, 2);
	ft_deltab(&compacted_env);
	return (127);
}

int		exec_file_env(t_env *env, char *right_path, char **command, int flags)
{
	char	**tab_env;
	char	**argv;
	int		i;
	char	**compacted_env;

	i = 1;
	while (command[i][0] == '-' || ft_strchr(command[i], '='))
		i++;
	compacted_env = compact_env(env);
	if (flags & PE_V)
		verbose(env, right_path, command[i]);
	argv = compact_argv_env(command, i);
	if (flags & PE_V)
		print_verbose_env(NULL, argv, 2);
	tab_env = compact_env(env);
	exec_env(right_path, argv, tab_env);
	ft_deltab(&argv);
	ft_deltab(&compacted_env);
	return (0);
}

int		launch_command_env(t_hustru *big_struc, int flags, char **command)
{
	t_env	*env;
	int		is_command;
	char	*right_path;
	char	**compacted_env;
	int i = 1;

	is_command = 1;
	env = parse_env(big_struc, command, flags, &is_command);
	while (command[i][0] == '-' || ft_strchr(command[i], '='))
		i++;
	compacted_env = compact_env(env);
	if (ft_tabstr(command, "PATH="))
		right_path = find_path(compacted_env, command[i]);
	else
		right_path = find_path(big_struc->path, command[i]);
	if (!right_path)
		return (print_err_env(compacted_env, command[i]));
	if (is_command && (flags & PE_I || ft_tabchr(command, '=')))
		exec_file_env(env, right_path, command, flags);
	return (0);
}

int		print_env(t_hustru *big_struc, char **command)
{
	if (!command[1])
		return (print_basic_env(big_struc->lkd_env, 0, 0));
	else
		return (parsing_env(big_struc, command));
}
