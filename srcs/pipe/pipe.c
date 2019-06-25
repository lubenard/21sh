/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/20 23:52:16 by lubenard          #+#    #+#             */
/*   Updated: 2019/06/25 15:52:54 by lubenard         ###   ########.fr       */
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

int		exec_pipe(t_env *lkd_env, char **path, int link[2], char ***command)
{
	char *exec_path;

	if (*(command + 1) != NULL)
		dup2(link[1], 1);
	close(link[0]);
	execve((exec_path = find_path(path, (*command)[0])),
	*command, compact_env(lkd_env));
	free(exec_path);
	return (0);
}

void	multiple_pipe(t_env *lkd_env, char ***command, char **path)
{
	int		link[2];
	pid_t	pid;
	int		fd_in;
	char	***tmp;

	tmp = command;
	fd_in = 0;
	while (*command != NULL)
	{
		if (pipe(link) == -1 || (pid = fork()) == -1)
			return ;
		if (pid == 0)
		{
			dup2(fd_in, 0);
			exec_pipe(lkd_env, path, link, command);
		}
		else
		{
			wait(NULL);
			close(link[1]);
			fd_in = link[0];
			command++;
		}
	}
	free_pipe(tmp);
}

int		handle_pipe(t_env *lkd_env, char **path, char *command)
{
	multiple_pipe(lkd_env, compact_command(command), path);
	return (0);
}
