/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/20 23:52:16 by lubenard          #+#    #+#             */
/*   Updated: 2019/05/27 16:05:24 by lubenard         ###   ########.fr       */
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

int		count_args(char **tab)
{
	int		i;

	i = 0;
	while (tab[i])
		i++;
	printf("Il y a %d elements\n", i);
	return (i);
}

char	***compact_command(char *command)
{
	char	***ret;
	char	**argv;
	int		i;

	i = 0;
	argv = ft_strsplit(command, '|');
	if (!(ret = (char ***)malloc(sizeof(char **) * (count_args(argv) + 1))))
		return (NULL);
	while (argv[i])
	{
		argv[i] = ft_strtrim(argv[i]);
		ret[i] = ft_strsplit(argv[i], ' ');
		printf("re[%d] vaut %s\n", i, ret[i][0]);
		i++;
		free(argv[i]);
	}
	free(argv);
	printf("ret[%d] vaut NULL\n", i);
	ret[i] = NULL;
	return (ret);
}

int		multiple_pipe(t_env *lkd_env, char ***command)
{
	int		link[2];
	pid_t	pid;
	int		fd_in;

	fd_in = 0;
	while (*command != NULL)
	{
		if (pipe(link) == -1 || (pid = fork()) == -1)
			return (0);
		if (pid == 0)
		{
			dup2(fd_in, 0);
			if (*(command + 1) != NULL)
				dup2(link[1], 1);
			close(link[0]);
			printf("command vaut %s et command[1] vaut %s et command[2] = %s\n", (*command)[0], (*command)[1], (*command)[2]);
			execve((*command)[0], *command, compact_env(lkd_env));
			perror("error: ");
			break ;
		}
		else
		{
			printf("Je suis la avec %s\n", (*command)[0]);
			wait(NULL);
			close(link[1]);
			fd_in = link[0];
			command++;
		}
	}
	return (0);
}

int		handle_pipe(t_env *lkd_env, char *command)
{
	/*
	** Only the last pipe is counted on Bash.
	*/
	if (ft_occur(command, '|') == 1)
		basic_pipe(lkd_env, command);
	else if (ft_occur(command, '|') > 1)
		multiple_pipe(lkd_env, compact_command(command));
	return (0);
}
