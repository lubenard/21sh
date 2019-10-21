/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/02 13:46:33 by lubenard          #+#    #+#             */
/*   Updated: 2019/10/21 15:46:47 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh21.h>

/*
** Tranform char * into char *** by splitting it by pipes then by spaces
*/

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
** Handle pipe and heredoc
*/

char	*pipe_heredoc(t_hustru *big_struc, char ***command)
{
	int		i;
	char	*str;

	i = 0;
	str = NULL;
	while (command[i])
	{
		if (ft_tabstr(command[i], "<<"))
		{
			remove_quote(&command[i]);
			big_struc->pipe_heredoc = heredoc(big_struc, command[i]);
		}
		i++;
	}
	return (str);
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
