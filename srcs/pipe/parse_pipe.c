/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/02 13:46:33 by lubenard          #+#    #+#             */
/*   Updated: 2019/10/23 12:47:53 by lubenard         ###   ########.fr       */
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
** Free the array created above
*/

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
		free(command[i++]);
		e = 0;
	}
	free(command);
	return (0);
}

/*
** Malloc pipes and create connections between them
*/

int		*prepare_pipe(t_hustru *big_struc, char ***compacted_command,
	char *command, int i)
{
	int		*pipes;
	int		e;
	char	*str;

	if (ft_strstr(command, "<<"))
	{
		big_struc->should_heredoc = 0;
		str = pipe_heredoc(big_struc, compacted_command);
	}
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
** Created to close multiple pipes
*/

void	close_pipe(int *pipes, int i)
{
	int j;

	j = 0;
	while (j != i)
		close(pipes[j++]);
}
