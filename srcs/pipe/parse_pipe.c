/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/02 13:46:33 by lubenard          #+#    #+#             */
/*   Updated: 2019/10/17 23:08:45 by lubenard         ###   ########.fr       */
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
		//printf("ret[%d] = %s\n", i, ret[i][0]);
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
** Malloc pipes and create connections between them
*/

int		*prepare_pipe(int i)
{
	int		*pipes;
	int		e;

	e = 0;
	if (!(pipes = (int *)malloc(sizeof(int) * (i * 2))))
		return (0);
	printf("Je cree %d pipes\n", i *2);
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
