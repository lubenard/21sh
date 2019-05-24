/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/20 23:52:16 by lubenard          #+#    #+#             */
/*   Updated: 2019/05/24 18:04:56 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../sh21.h"

/*
** Only exec cat | grep firefox for now
*/

int		basic_pipe(t_env *lkd_env, char *command)
{
	int		link[2];
	int		pid;
	char	**env;
	char *argv[] = {"grep", "firefox", NULL};
	char *argv2[] = {"cat", NULL};

	(void)command;
	env = compact_env(lkd_env);
	if (pipe(link) == -1 || (pid = fork()) == -1)
		return (0);
	if (pid == 0)
	{
		printf("j'execute grep\n");
		dup2(link[0], 0);
		close(link[1]);
		execve("/usr/bin/grep", argv, env);
	}
	else
	{
		printf("j'execute cat\n");
		dup2(link[1], 1);
		close(link[0]);
		execve("/bin/cat", argv2, env);
	}
	return (0);
}

char	***compact_command(char *command)
{
	char	***ret;
	char	**argv;
	char	**av;

	int		e = 0;
	int		i = 0;
	ret = NULL;
	argv = ft_strsplit(command, '|');
	while (argv[i])
	{
		argv[i] = ft_strtrim(argv[i]);
		printf("argv[%d] vaut '%s'\n", i, argv[i]);
		av = ft_strsplit(argv[i], ' ');
		while (av[e])
		{
			printf("av[%d] = %s\n", e, av[e]);
			e++;
		}
		i++;
		e = 0;
	}

	return (ret);
}

int		multiple_pipe(t_env *lkd_env, char ***command)
{
	int		link[2];
	pid_t	pid;
	int		fd_in;
	int		i;

	i = 0;
	fd_in = 0;
	while (command[i] != NULL)
	{
		if (pipe(link) == -1 || (pid = fork()) == -1)
			return (0);
		if (pid == 0)
		{
			dup2(fd_in, 0);
			if (*(command + 1) != NULL)
				dup2(link[1], 1);
			close(link[0]);
			execve((*command)[0], *command, compact_env(lkd_env));
			exit(EXIT_FAILURE);
		}
		else
		{
			wait(NULL);
			close(link[1]);
			fd_in = link[0];
			i++;
		}
	}
	return (0);
}

int		handle_pipe(t_env *lkd_env, char *command)
{
	(void)command;
	/*
	 ** Only the last pipe is counted on Bash.
	 */
	if (ft_occur(command, '|') == 1)
		basic_pipe(lkd_env, command);
	else if (ft_occur(command, '|') > 1)
		multiple_pipe(lkd_env, compact_command(command));
	return (0);
}
