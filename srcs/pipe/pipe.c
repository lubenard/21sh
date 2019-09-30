/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/20 23:52:16 by lubenard          #+#    #+#             */
/*   Updated: 2019/09/30 16:58:56 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh21.h>

char	***compact_command(char *command)
{
	char	***ret;
	char	**argv;
	char	*tmp;
	int		i;

	i = 0;
	if (command[ft_strlen(command) - 1] == '|')
		return (NULL);
	argv = ft_strsplit(command, '|');
	if (!(ret = (char ***)malloc(sizeof(char **) * (ft_tablen(argv) + 1))))
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

void	close_pipe(int *pipes, int i)
{
	int j;

	j = 0;
	while (j != i)
		close(pipes[j++]);
}

int		count_args_triple_tab(char ***tab)
{
	int		i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}

int		*prepare_pipe(int i)
{
	int		*pipes;
	int		e;

	e = 0;
	if (!(pipes = (int *)malloc(sizeof(int) * (i * 2))))
		return (0);
	while (e != i * 2)
	{
		pipe(pipes + e);
		e += 2;
	}
	return (pipes);
}

int		wait_pipe(int i, int *pipes, char ***tab)
{
	int e;
	int status;

	e = 0;
	close_pipe(pipes, i * 2);
	while (e < i + 1)
	{
		wait(&status);
		e++;
	}
	free(pipes);
	return (free_pipe(tab));
}

void	exec_pipe(int j, int k, int *pipes, char ***tab)
{
	if (j != 0)
		dup2(pipes[k], 0);
	if (tab[j + 1] && j != 0)
		dup2(pipes[k + 3], 1);
	if (j == 0)
		dup2(pipes[1], 1);
}

int		handle_pipe(t_hustru *big_struc, char *command)
{
	int		i;
	char	***tab;
	int		*pipes;
	int		j;
	int		k;

	if ((tab = compact_command(command)) == NULL)
		return (display_error("Pipe: Invalid pipe\n", NULL));
	j = 0;
	k = 0;
	i = count_args_triple_tab(tab) - 1;
	pipes = prepare_pipe(i);
	while (tab[j])
	{
		if (fork() == 0)
		{
			exec_pipe(j, k, pipes, tab);
			close_pipe(pipes, i * 2);
			basic_command(big_struc, tab[j], exec_without_fork);
		}
		if (j != 0)
			k += 2;
		j++;
	}
	return (wait_pipe(i, pipes, tab));
}
