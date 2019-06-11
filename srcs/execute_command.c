/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/15 16:46:50 by lubenard          #+#    #+#             */
/*   Updated: 2019/06/11 08:47:18 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh21.h>

pid_t	g_pid;

char	**compact_env(t_env *lkd_env)
{
	int		i;
	char	**env;
	t_env	*tmp;

	i = 0;
	tmp = lkd_env;
	while (lkd_env)
	{
		i++;
		lkd_env = lkd_env->next;
	}
	if (!(env = (char **)malloc(sizeof(char *) * (i + 1))))
		return (NULL);
	i = 0;
	while (tmp)
	{
		env[i] = tmp->env_line;
		tmp = tmp->next;
		i++;
	}
	env[i] = NULL;
	return (env);
}

char	*reduce_command(char *command)
{
	int		i;
	int		e;
	char	*ret;

	i = 0;
	e = 0;
	if (access(command, X_OK) == -1 || get_error_exec(command, 0))
	{
		get_error_exec(command, 1);
		free(command);
		return (NULL);
	}
	if ((command[0] == '/' || !ft_strncmp(command, "./", 2)
	|| !ft_strncmp(command, "..", 2)) && command[2])
	{
		i = ft_strlen(command);
		while (command[i] != '/')
			i--;
		while (command[i + e] && command[i + e] != ' ')
			e++;
		ret = ft_strlower(ft_strsub(command, i + 1, e - 1));
		return (ret);
	}
	return (NULL);
}

char	*check_exec_rights(char *get_right_path, char *command)
{
	char *path;

	if (access((path = ft_strjoin(get_right_path, command)), X_OK)
	|| get_error_exec(path, 0))
	{
		get_error_exec(path, 1);
		free(path);
		return (NULL);
	}
	free(path);
	return (ft_strdup(command));
}

int		exec_command_gen(char *path, char **argv, char **env)
{
	g_pid = fork();
	signal(SIGINT, handle_signals_proc);
	if (g_pid < 0)
		return (0);
	if (g_pid == 0)
	{
		execve(path, argv, env);
	}
	wait(&g_pid);
	return (free_after_exec(path, argv, env));
}

int		execute_command(char *get_right_path, char *command,
	char **argv, char **env)
{
	char	path[6000];

	if (command[0] == '/' || command[0] == '.')
		command = reduce_command(command);
	else
		command = check_exec_rights(get_right_path, command);
	if (command == NULL)
		return (free_after_exec(get_right_path, argv, env));
	g_pid = fork();
	signal(SIGINT, handle_signals_proc);
	if (g_pid < 0)
		return (0);
	if (g_pid == 0)
	{
		ft_strcpy(path, get_right_path);
		execve(ft_strcat(path, command), argv, env);
	}
	wait(&g_pid);
	free(command);
	return (free_after_exec(get_right_path, argv, env));
}
