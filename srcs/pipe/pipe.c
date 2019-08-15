/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/20 23:52:16 by lubenard          #+#    #+#             */
/*   Updated: 2019/08/15 18:44:11 by lubenard         ###   ########.fr       */
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

void	close_pipe(int *pipes, int i)
{
	int j;

	j = 0;
	while (j != i)
	{
		//dprintf(2, "je ferme pipes[%d]\n", j);
		close(pipes[j++]);
	}
	dprintf(2, "All (%d) pipes have been closed\n", i);
	//dprintf(2, "**************************\n");
}



int		handle_pipe(t_hustru *big_struc, char *command)
{

	int		status;
	int		i;
	char	***tab;
	int		*pipes;
	int		e;
	int		j;
	int		k;

	tab = compact_command(command);
	e = 0;
	/*while (*tab)
	{
		printf("tab[%d] vaut %s\n", e++, *tab[0]);
		++tab;
	}*/
	//printf("-----------------------------\n");
	e = 0;
	j = 0;
	k = 0;
	i = ft_occur(command, '|'); // To fix if a pipe is at the end
	printf("I vaut %d\n", i);
	printf("close fera %d\n", i * 2);
	printf("wait fera %d\n", i + 1);
	if (!(pipes = (int *)malloc(sizeof(int) * (i * 2))))
		return (0);
	while (e != i * 2)
	{
		printf("je pipe a + %d\n", e);
		pipe(pipes + e);
		e += 2;
	}
	e = 0;
	/*if (fork() == 0)
	{
		dup2(pipes[1], 1);
		close_pipe(pipes, i * 2);
		execve(find_path(big_struc->path, tab[j][0]), tab[j], compact_env(big_struc->lkd_env));
	}
	else
	{*/
		while (tab[j])
		{
			if (fork() == 0)
			{
				dprintf(2, "J'exec tab[%d][0] = %s\n", j, tab[j][0]);
				if (j != 0)
				{
					dprintf(2, "dup2(pipes[%d], 0)\n", k);
					dup2(pipes[k], 0);
				}
				if (tab[j + 1] && j != 0)
				{
					dprintf(2, "dup2(pipes[%d], 1)\n", k + 3);
					dup2(pipes[k + 3], 1);
				}
				if (j == 0)
				{
					dprintf(2, "dup2(pipes[%d], 1)\n", k + 1);
					dup2(pipes[1], 1);
				}
				close_pipe(pipes, i * 2);
				execve(find_path(big_struc->path, tab[j][0]), tab[j], compact_env(big_struc->lkd_env));
			}
			if (j != 0)
				k += 2;
			j++;
		}
/*		if (fork() == 0)
		{
			dprintf(2, "J'exec derniere tab\n");
			dup2(pipes[6], 0);
			close_pipe(pipes, i * 2);
			execve(find_path(big_struc->path, tab[j][0]), tab[j], compact_env(big_struc->lkd_env));
		}*/
		/*if (fork() == 0)
		{
			dup2(pipes[0], 0);
			dup2(pipes[3], 1);
			close_pipe(pipes, i * 2);
			execve(find_path(big_struc->path, tab[1][0]), tab[1], compact_env(big_struc->lkd_env));
		}
		else
		{
			if (fork() == 0)
			{
				dup2(pipes[2], 0);
				dup2(pipes[5], 1);
				close_pipe(pipes, i * 2);
				execve(find_path(big_struc->path, tab[2][0]), tab[2], compact_env(big_struc->lkd_env));
			}
			else
			{
				if (fork() == 0)
				{
					dup2(pipes[4], 0);
					dup2(pipes[7], 1);
					close_pipe(pipes, i * 2);
					execve(find_path(big_struc->path, tab[3][0]), tab[3], compact_env(big_struc->lkd_env));
				}
				else
				{
					if (fork() == 0)
					{
					dup2(pipes[6], 0);
					close_pipe(pipes, i * 2);
					execve(find_path(big_struc->path, tab[4][0]), tab[4], compact_env(big_struc->lkd_env));
					}
				}
			}
		}*/
	//}
	close_pipe(pipes, i * 2);
	while (e < i + 1)
	{
		wait(&status);
		e++;
	}
	free(pipes);
	return(free_pipe(tab));
}

int		handle_pipe2(t_hustru *big_struc, char *command)
{
	char	***tab;
	char	***tmp;
	int		pipe_fd[2];
	pid_t	pid;
	int fd_in;

	tab = compact_command(command);
	tmp = tab;
	/*while (*tab)
	  {
	  printf("tab vaut %s\n", *tab[0]);
	  ++tab;
	  }
	  printf("-----------------------------\n");*/
	tab = tmp;
	fd_in = 0;
	reset_shell_attr(0);
	while (*tab != NULL)
	{
		if (pipe(pipe_fd) == -1 || (pid = fork()) == -1)
			return (-1);
		if (pid == 0)
		{
			printf("Je suis enfant\n");
			dup2(fd_in, 0);
			if (*(tab + 1) != NULL)
				dup2(pipe_fd[1], 1);
			close(pipe_fd[1]);
			execve(find_path(big_struc->path, *tab[0]), *tab, compact_env(big_struc->lkd_env));
			exit(0);
		}
		else
		{
			printf("Je suis parent\n");
			close(pipe_fd[0]);
			fd_in = pipe_fd[0];
			tab++;
		}
	}
	set_none_canon_mode(0);
	free_pipe(tmp);
	return (0);
	return(free_pipe(tmp));
}
