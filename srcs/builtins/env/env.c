/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/04 14:09:48 by lubenard          #+#    #+#             */
/*   Updated: 2019/11/30 19:09:56 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <env.h>
#include <sh21.h>
#include <stdio.h>

void	fill_env(t_env *lkd_env, t_env *env, char **command, int i)
{
	t_env	*new_element;
	char	*fie;
	char	*to_search;
	char	*to_extract;

	if ((fie = find_in_env(env, extract_first(command[i], '='))))
		fill_env2(env, command, i);
	to_search = extract_first(command[i], '=');
	while (lkd_env)
	{
		to_extract = extract_first(lkd_env->env_line, '=');
		if (!ft_strcmp(to_search, to_extract))
		{
			ft_strcpy(lkd_env->env_line, command[i]);
			ft_strdel(&to_search);
			ft_strdel(&to_extract);
			return ;
		}
		ft_strdel(&to_extract);
		lkd_env = lkd_env->next;
	}
	if (fie == NULL)
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
	ft_strdel(&to_search);
	free(fie);
}

int		print_err_env(char **compacted_env, char **argv, char *comm)
{
	ft_putstr_fd("No file found with the following name: ", 2);
	ft_putendl_fd(comm, 2);
	ft_deltab(&argv);
	ft_deltab(&compacted_env);
	return (127);
}

int		exec_file_env(t_env *env, char **command, int flags)
{
	char	**tab_env;
	char	*right_path;
	char	**argv;
	int		i;
	char	**compacted_env;

	i = 1;
	while (command[i][0] == '-' || ft_strchr(command[i], '='))
		i++;
	compacted_env = compact_env(env);
	right_path = find_path(compacted_env, command[i]);
	if (flags & PE_V)
		verbose(env, right_path, command[i]);
	argv = compact_argv_env(command, i);
	if (flags & PE_V)
		print_verbose_env(NULL, argv, 2);
	if (right_path == NULL)
		return (print_err_env(compacted_env, argv, command[i]));
	tab_env = compact_env(env);
	exec_env(right_path, argv, tab_env);
	ft_deltab(&argv);
	ft_deltab(&compacted_env);
	return (0);
}

int		exec_custom_env(t_env *env, char **command,
	t_hustru *big_struc, int flags)
{
	int		ret;
	int		save;
	int		i;

	(void)big_struc;
	save = 0;
	i = 0;
	ret = 0;
	//ret = (flags & PE_I) ? exec_file_env(NULL, command, flags) :
	exec_file_env(env, command, flags);
	return (ret);
}

int		launch_command_env(t_hustru *big_struc, int flags, char **command)
{
	t_env	*env;
	int		is_command;
	t_env	*reenv;

	reenv = ft_envcpy(big_struc->lkd_env);
	(void)flags;
	(void)command;
	(void)is_command;
	(void)env;
	is_command = 1;
	env = parse_env(reenv, command, flags, &is_command);
	if (is_command == 1 && (flags & PE_I || ft_tabchr(command, '=')))
		exec_custom_env(reenv, command, big_struc, flags);
	else if (is_command == 1)
			exec_file_env(reenv, command, flags);
	//free_env(env);
	//free_env(reenv);
	return (0);
}

int		print_env(t_hustru *big_struc, char **command)
{
	if (!command[1])
		return (print_basic_env(big_struc->lkd_env, 0, 0));
	else
		return (parsing_env(big_struc, command));
}
