/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/20 23:52:16 by lubenard          #+#    #+#             */
/*   Updated: 2019/08/11 16:12:22 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh21.h>

int		count_args(char **tab)
{
	int		i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}

char	***compact_command(char *command)
{
	char	***ret;
	char	**argv;
	char	*tmp;
	int		i;

	i = 0;
	argv = ft_strsplit(command, '|');
	if (!(ret = (char ***)malloc(sizeof(char **) * (count_args(argv) + 1))))
		return (NULL);
	while (argv[i])
	{
		tmp = ft_strtrim(argv[i]);
		ret[i] = ft_strsplit(tmp, ' ');
		free(argv[i]);
		i++;
		free(tmp);
	}
	free(argv);
	ret[i] = NULL;
	return (ret);
}

int		free_pipe(char ***command)
{
	int		i;
	int		e;
	int		k;

	k = 0;
	i = 0;
	e = 0;
	while (command[i])
	{
		while (command[i][e])
		{
			free(command[i][e]);
			e++;
		}
		free(command[i]);
		i++;
		e = 0;
	}
	free(command);
	return (0);
}

int		handle_pipe(t_hustru *big_struc, char *command)
{
	char	***tab;
	int		pipe_fd[2];
	pid_t	pid;

	(void)big_struc;
	(void)command;

	tab = compact_command(command);
	while (*tab)
	{
		if (pipe(pipe_fd) || (pid = fork()) == -1)
			return (-1);
		if (!pid)
		{
			printf("je suis enfant\n");
			close(pipe_fd[1]);
			dup2(pipe_fd[0], 0);
			tab++;
			execve(find_path(big_struc->path, *tab[0]), *tab, compact_env(big_struc->lkd_env));
		}
		else
		{
			printf("Je suis parent\n");
			close(pipe_fd[0]);
			dup2(pipe_fd[1], 1);
			execve(find_path(big_struc->path, *tab[0]), *tab, compact_env(big_struc->lkd_env));
		}
	}
	printf("returning\n");
	return (0);
}

int		handle_pipe2(t_hustru *big_struc, char *command)
{
	char	***tab;
	char	***tmp;
	int		pipe_fd[2];
	pid_t	pid;
	int fd_in;

	tab = compact_command(command);
	tmp = tab;
	while (*tab)
	{
		printf("tab vaut %s\n", *tab[0]);
		++tab;
	}
	printf("-----------------------------\n");
	tab = tmp;
	fd_in = 0;
	//reset_shell_attr(0);
	while (*tab != NULL)
	{
		if (pipe(pipe_fd) == -1 || (pid = fork()) == -1)
			return (-1);
		if (pid == 0)
		{
			printf("Je suis enfant\n");
			dup2(fd_in, 0);
			if (*(tab + 1) != NULL)
				dup2(pipe_fd[1], 1);
			close(pipe_fd[1]);
			execve(find_path(big_struc->path, *tab[0]), *tab, compact_env(big_struc->lkd_env));
			exit(0);
		}
		else
		{
			printf("Je suis parent\n");
			close(pipe_fd[0]);
			fd_in = pipe_fd[0];
			tab++;
		}
	}
	//set_none_canon_mode(0);
	free_pipe(tmp);
	return (0);
	//return(free_pipe(tmp));
}
