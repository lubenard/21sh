/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/20 23:52:16 by lubenard          #+#    #+#             */
/*   Updated: 2019/08/09 17:32:11 by lubenard         ###   ########.fr       */
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
	char	***tmp;
	int		pipe_fd[2];
	pid_t	pid;
	char	*path;

	(void)big_struc;
	tab = compact_command(command);
	tmp = tab;

	while (*tab)
	{
		printf("tab vaut %s\n", *tab[0]);
		++tab;
	}
	tab = tmp;
	while (*tab)
	{
		if (pipe(pipe_fd) == -1 || (pid = fork()) == -1)
			return (-1);
		if (!pid)
		{
			printf("Exec de %s\n", *tab[0]);
			dup2(pipe_fd[1], 1);
			exec_command_gen(path = find_path(big_struc->path, *tab[0]),
			*tab, compact_env(big_struc->lkd_env));
		}
		else
		{
			tab++;
			printf("Exec de %s\n", *tab[0]);
			if (tab + 1)
				exec_command_gen(path = find_path(big_struc->path, ++(*tab[0])),
			*tab, compact_env(big_struc->lkd_env));
			close(pipe_fd[1]);
		}
	}
	return (0);
	//return(free_pipe(tmp));
}
