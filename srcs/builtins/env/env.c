/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/04 14:09:48 by lubenard          #+#    #+#             */
/*   Updated: 2019/12/03 10:09:53 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <env.h>
#include <sh21.h>
# include <stdio.h>

void	fill_env(t_env *env, char **command, int i)
{
	t_env	*new_element;
	char	*to_search;
	char	*find;

	to_search = extract_first(command[i], '=');
	find = find_in_env(env, ft_strdup(to_search));
	if (env && find)
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
		ft_strdel(&to_search);
	}
	ft_strdel(&find);
}

int		print_err_env(t_env *env, char **compacted_env, char *comm)
{
	ft_putstr_fd("No file found with the following name: ", 2);
	ft_putendl_fd(comm, 2);
	free_env(env);
	free(compacted_env);
	return (127);
}

int		exec_file_env(t_env *env, char *right_path, char **command, int flags)
{
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
	exec_env(right_path, argv, compacted_env);
	ft_deltab(&argv);
	return (0);
}

char	*find_path_env(t_env *env, char *command)
{
	char *get_path_line;
	char *right_path;
	char **path;

	get_path_line = find_in_env(env, ft_strdup("PATH"));
	path = get_path(get_path_line);
	right_path = find_path(path, command);
	ft_deltab(&path);
	return (right_path);
}

int		launch_command_env(t_hustru *big_struc, int flags, char **command)
{
	t_env	*env;
	int		is_command;
	char	*right_path;
	char	**compacted_env;
	int		i;

	i = 1;
	is_command = 1;
	env = parse_env(big_struc, command, flags, &is_command);
	while (command[i][0] == '-' || ft_strchr(command[i], '='))
		i++;
	compacted_env = compact_env(env);
	right_path = (ft_tabstr(command, "PATH=")) ?
	find_path_env(env, command[i])
	: find_path(big_struc->path, command[i]);
	if (!right_path)
		return (print_err_env(env, compacted_env, command[i]));
	if (is_command)
		exec_file_env(env, right_path, command, flags);
	free(compacted_env);
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
