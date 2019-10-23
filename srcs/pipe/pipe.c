/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/20 23:52:16 by lubenard          #+#    #+#             */
/*   Updated: 2019/10/23 12:38:05 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh21.h>

/*
** Launch command pipes
*/

void	launch_command_pipe(t_hustru *big_struc, char ***tab, int j)
{
	if (decide_commande(big_struc, tab[j], exec_without_fork, 0) == 1)
		free_pipe(tab);
	exit(0);
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
** Go to next pipes
*/

void	count_pipes(int *j, int *k)
{
	if (*j != 0)
		(*k) += 2;
	(*j)++;
}

/*
** Launch pipes
*/

int		handle_pipe(t_hustru *big_struc, char *command)
{
	int		i;
	int		j;
	int		k;
	char	***tab;
	int		*pipes;

	if ((tab = compact_command(command)) == NULL)
		return (display_error("Pipe: Invalid pipe\n", NULL));
	j = 0;
	k = 0;
	i = count_args_triple_tab(tab) - 1;
	pipes = prepare_pipe(big_struc, tab, command, i);
	while (tab[j])
	{
		if (!is_valid_command(big_struc, tab[j]) && !fork())
		{
			exec_pipe(j, k, pipes, tab);
			do_heredoc_pipe(big_struc, tab, j);
			close_pipe(pipes, i * 2);
			launch_command_pipe(big_struc, tab, j);
		}
		count_pipes(&j, &k);
	}
	return (wait_pipe(i, pipes, tab));
}
