/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_old.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/20 23:52:16 by lubenard          #+#    #+#             */
/*   Updated: 2019/10/11 18:59:26 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh21.h>

/*
** Like ft_strlen but for triple array
*/

int		count_args_triple_tab(char ***tab)
{
	int		i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}

/*
** Malloc pipes and create connections between them
*/

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

/*
** Wait until all exceution are finished
*/

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

/*
** Make the good rediections
*/

void	exec_pipe(int j, int k, int *pipes, char ***tab)
{
	if (j != 0)
		dup2(pipes[k], 0);
	if (tab[j + 1] && j != 0)
		dup2(pipes[k + 3], 1);
	if (j == 0)
		dup2(pipes[1], 1);
}

/*
** Launch pipes
*/

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
