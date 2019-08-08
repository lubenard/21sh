/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/15 16:46:50 by lubenard          #+#    #+#             */
/*   Updated: 2019/08/08 14:53:10 by lubenard         ###   ########.fr       */
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
	if (access(command, X_OK) == -1 || get_error_exec(command))
	{
		invalid_command(command);
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

int		check_exec_rights(char *path)
{
	if (access(path, X_OK)
	|| get_error_exec(path))
	{
		invalid_command(path);
		free(path);
		return (1);
	}
	return (0);
}

int		exec_command_gen(char *path, char **argv, char **env)
{
	if (check_exec_rights(path))
	{
		ft_putstr_fd("You cannot execute the file (´ ͡༎ຶ ͜ʖ ͡༎ຶ )\n", 2);
		return (1);
	}
	printf("C'es une commande generale\n");
	g_pid = fork();
	reset_shell_attr(0);
	signal(SIGINT, handle_signals_proc);
	if (g_pid < 0)
		return (0);
	if (g_pid == 0)
		execve(path, argv, env);
	wait(&g_pid);
	set_none_canon_mode(0);
	return (free_after_exec(path, argv, env));
}

int		execute_command(char *get_right_path, char *command,
	char **argv, char **env)
{
	char	path[6000];

	
	if (command[0] == '/' || command[0] == '.')
		command = reduce_command(command);
	if (check_exec_rights(get_right_path))
	{
		ft_putstr_fd("You cannot execute the file (´ ͡༎ຶ ͜ʖ ͡༎ຶ )\n", 2);
		return (1);
	}
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
