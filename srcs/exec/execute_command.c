/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/15 16:46:50 by lubenard          #+#    #+#             */
/*   Updated: 2019/09/19 14:11:59 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh21.h>

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

int		check_exec_rights(char *path)
{
	if (access(path, X_OK)
	|| get_error_exec(path))
	{
		invalid_command(path);
		ft_putstr_fd("You cannot execute the file (´ ͡༎ຶ ͜ʖ ͡༎ຶ )\n", 2);
		free(path);
		return (0);
	}
	return (1);
}

int		exec_command_gen(char *path, char **argv, char **env)
{
	pid_t	g_pid;

	if (!check_exec_rights(path))
		return (1);
	g_pid = fork();
	reset_shell_attr(0);
	signal(SIGINT, handle_signals_proc);
	if (g_pid < 0)
	{
		ft_putendl_fd("ymarsh: Error during execution: fork failed", 2);
		return (1);
	}
	if (!g_pid)
		execve(path, argv, env);
	wait(&g_pid);
	set_none_canon_mode(0);
	return (free_after_exec(path, env));
}
