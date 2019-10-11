/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 18:24:08 by lubenard          #+#    #+#             */
/*   Updated: 2019/10/11 19:00:01 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh21.h>

int		count_args_triple_tab(char ***tab)
{
	int		i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
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

int		handle_pipe(t_hustru *big_struc, char *command)
{
	int		i;
	char	***tab;
	int		*pipes;
	int		e;
	int		j;
	int		k;

	tab = compact_command(command);
	e = 0;
	j = 0;
	k = 0;
	i = count_args_triple_tab(tab) - 1;
	if (!(pipes = (int *)malloc(sizeof(int) * (i * 2))))
		return (0);
	while (e != i * 2)
	{
		pipe(pipes + e);
		e += 2;
	}
	e = 0;
	while (tab[j])
	{
		if (fork() == 0)
		{
			if (j != 0)
				dup2(pipes[k], 0);
			if (tab[j + 1] && j != 0)
				dup2(pipes[k + 3], 1);
			if (j == 0)
				dup2(pipes[1], 1);
			close_pipe(pipes, i * 2);
			//exec_without_fork(big_struc, tab[j]);
			basic_command(big_struc, tab[j], exec_without_fork);
			//execve(find_path(big_struc->path, tab[j][0]), tab[j], compact_env(big_struc->lkd_env));
		}
		if (j != 0)
			k += 2;
		j++;
	}
	return (wait_pipe(i, pipes, tab));
}
