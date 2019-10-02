/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/15 16:46:50 by lubenard          #+#    #+#             */
/*   Updated: 2019/10/02 18:25:16 by lubenard         ###   ########.fr       */
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

/*
** Check if you have the rights to execute the command
*/

int		check_exec_rights(char *path)
{
	if (access(path, X_OK) || get_error_exec(path))
	{
		invalid_command(path);
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
	char *path;
	char **env;

	printf("Je ne fork pas\n");
	if (!(path = find_path(big_struc->path, argv[0])))
	{
		free(path);
		return (invalid_command(argv[0]));
	}
	if (!check_exec_rights(path))
		return (1);
	reset_shell_attr(0);
	//signal(SIGINT, handle_signals_proc);
	execve(path, argv, env = compact_env(big_struc->lkd_env));
	set_none_canon_mode(0);
	return (free_after_exec(path, env));
}

/*
** Exec but fork
*/

int		exec_command_gen(t_hustru *big_struc, char **argv)
{
	pid_t	pid;
	char	*path;
	char	**env;

	printf("Je fork\n");
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
	wait(&pid);
	set_none_canon_mode(0);
	return (free_after_exec(path, env));
}
