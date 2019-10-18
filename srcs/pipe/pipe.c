/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/20 23:52:16 by lubenard          #+#    #+#             */
/*   Updated: 2019/10/18 19:23:29 by lubenard         ###   ########.fr       */
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
** Launch command pipes
*/

void	launch_command_pipe(t_hustru *big_struc, char ***tab, int j, int a)
{
	if (decide_commande(big_struc, tab[j], exec_without_fork, 0) == 1)
		free_pipe(tab);
	if (a == 0)
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
	{
		printf("Je redirige pipes[%d], 0\n", k);
		dup2(pipes[k], 0);
	}
	if (tab[j + 1] && j != 0)
	{
		printf("Je redirige pipes[%d], 1\n", k + 3);
		dup2(pipes[k + 3], 1);
	}
	if (j == 0)
	{
		printf("Je redirige pipes[%d], 1\n", 1);
		dup2(pipes[1], 1);
	}
}

int		is_valid_command(t_hustru *big_struc, char **argv)
{
	char	*path;

	if (!(path = find_path(big_struc->path, argv[0])))
	{
		free(path);
		return (invalid_command(argv[0]));
	}
	free(path);
	return (0);
}

/*
** Launch Pipes without forking
*/

int		handle_pipe_w_fork(t_hustru *big_struc, char *command)
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
	pipes = prepare_pipe(big_struc, tab ,command,i);
	while (tab[j])
	{
		exec_pipe(j, k, pipes, tab);
		close_pipe(pipes, i * 2);
		launch_command_pipe(big_struc, tab, j, 1);
		if (j != 0)
			k += 2;
		j++;
	}
	close_pipe(pipes, i * 2);
	free(pipes);
	return (free_pipe(tab));
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
	pipes = prepare_pipe(big_struc, tab, command, i);
	//if (big_struc->pipe_heredoc)
	//{
	//	printf("J'envoie %s sur pipe[1]\n", big_struc->pipe_heredoc);
//		ft_putstr_fd(big_struc->pipe_heredoc, pipes[1]);
//	}
	while (tab[j])
	{
		if (!is_valid_command(big_struc, tab[j]) && fork() == 0)
		{
			exec_pipe(j, k, pipes, tab);
			//exec_pipe(j, k, pipes, tab);
			if (big_struc->pipe_heredoc)
			{
				printf("J'envoie\n%s sur pipe[1] dans %s\n", big_struc->pipe_heredoc, tab[j][0]);
				ft_putstr_fd(big_struc->pipe_heredoc, pipes[1]);
			}
			close_pipe(pipes, i * 2);
			launch_command_pipe(big_struc, tab, j, 0);
		}
		if (j != 0)
			k += 2;
		j++;
	}
	return (wait_pipe(i, pipes, tab));
}
