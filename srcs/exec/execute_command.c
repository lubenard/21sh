/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/15 16:46:50 by lubenard          #+#    #+#             */
/*   Updated: 2019/12/03 01:04:13 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh21.h>

/*
** Compact linked list into double array
*/

char	**compact_env(t_env *lkd_env)
{
	int		i;
	char	**env;
	t_env	*tmp;

	i = 0;
	tmp = lkd_env;
	while (lkd_env)
	{
		if (ft_strcmp(lkd_env->env_line, ""))
			i++;
		lkd_env = lkd_env->next;
	}
	if (!(env = (char **)malloc(sizeof(char *) * (i + 1))))
		return (NULL);
	i = 0;
	while (tmp)
	{
		if (ft_strcmp(tmp->env_line, ""))
			env[i++] = tmp->env_line;
		tmp = tmp->next;
	}
	env[i] = NULL;
	return (env);
}

/*
** Check if you have the rights to execute the command
*/

int		check_exec_rights(char *path)
{
	if (access(path, X_OK) || get_error_exec(path))
	{
		ft_putstr_fd("You cannot execute the file (´ ͡༎ຶ ͜ʖ ͡༎ຶ )\n", 2);
		free(path);
		return (0);
	}
	return (1);
}

/*
** exec but do not fork
*/

int		exec_without_fork(t_hustru *big_struc, char **argv)
{
	char	*path;
	char	**env;

	if (!(path = find_path(big_struc->path, argv[0])))
	{
		free(path);
		return (invalid_command(argv[0]));
	}
	if (!check_exec_rights(path))
		return (1);
	reset_shell_attr(0);
	execve(path, argv, env = compact_env(big_struc->lkd_env));
	set_none_canon_mode(0);
	return (free_after_exec(path, env, 0));
}

/*
** Exec but fork
*/

int		exec_command_gen(t_hustru *big_struc, char **argv)
{
	pid_t	pid;
	char	*path;
	char	**env;
	int		statval;

	if (!(path = find_path(big_struc->path, argv[0])))
	{
		free(path);
		return (invalid_command(argv[0]));
	}
	if (!check_exec_rights(path))
		return (1);
	if ((pid = fork()) < 0)
		return (display_error("ymarsh: error: fork failed", NULL));
	reset_shell_attr(0);
	signal(SIGINT, handle_signals_proc);
	env = compact_env(big_struc->lkd_env);
	if (!pid)
		execve(path, argv, env);
	waitpid(pid, &statval, WUNTRACED | WCONTINUED);
	set_none_canon_mode(0);
	return (free_after_exec(path, env, statval));
}
