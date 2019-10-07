/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_redir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <lubenard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 01:56:26 by lubenard          #+#    #+#             */
/*   Updated: 2019/10/07 03:51:51 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh21.h>

/*
** Have to rewrite the redir: here is how it works
** 1) create files
** 2) Make the god redirections
** 3) Execute the command
*/

int		count_args_redir(char **tab, int i);

int		is_command_redir(int **fds, char **command, int  j, int *k)
{
	int fd;

	if (access(command[j], F_OK) == -1)
	{
		if ((fd = open(command[j], O_CREAT, 0644) < 0))
			return (display_error("ymarsh: error while creating file ",
					command[j]));
	}
	if ((ft_strchr(command[j - 1], '>') || ft_strchr(command[j - 1], '<'))
	&& !ft_strchr(command[j - 1], '&'))
	{
		printf("[Fill fds tab] Je rajoute %s\n", command[j]);
		if (ft_occur(command[j - 1], '>') == 1)
			(*fds)[(*k)++] = open(command[j], O_WRONLY | O_TRUNC);
		else if (ft_occur(command[j - 1], '>') == 2)
			(*fds)[(*k)++] = open(command[j], O_WRONLY | O_APPEND);
	}
	else if (ft_strchr(command[j - 1], '>') && ft_strchr(command[j - 1], '<'))
	{
		if (ft_occur(command[j - 1], '>') == 1)
			(*fds)[(*k)++] = open(command[j], O_WRONLY | O_TRUNC);
		else if (ft_occur(command[j - 1], '>') == 2)
			(*fds)[(*k)++] = open(command[j], O_WRONLY | O_APPEND);
	}
	return (0);
}

int		is_command(char ***exec_command, char **command, int  j, int *i)
{
	if (j > 0)
	{
		if ((ft_strchr(command[j - 1], '>') || ft_strchr(command[j - 1], '<'))
		&& ft_strchr(command[j - 1], '&'))
		{
			printf("[Adding to command] Je rajoute %s\n", command[j]);
			(*exec_command)[(*i)++] = command[j];
			return (1);
		}
		else if (!ft_strchr(command[j - 1], '>')
		&& !ft_strchr(command[j - 1], '<'))
		{
			printf("[Count args redir] Je rajoute %s\n", command[j]);
			(*exec_command)[(*i)++] = command[j];
			return (1);
		}
	}
	else
	{
		printf("[Adding to command] Je rajoute %s\n", command[j]);
		(*exec_command)[(*i)++] = command[j];
		return (1);
	}
	return (0);
}

int		fill_arrays(char **command, int **fds, char ***exec_command)
{
	int i;
	int j;
	int k;

	j = 0;
	i = 0;
	k = 0;
	while (command[j])
	{
		printf("[filling] Je regarde %s\n", command[j]);
		if (!ft_strchr(command[j], '>') && !ft_strchr(command[j], '<'))
		{
			if (!is_command(exec_command, command, j, &i))
				is_command_redir(fds, command, j, &k);
		}
		j++;
	}
	*exec_command[j] = NULL;
	return (0);
}

int		init_arrays(char **command, int **fds, char ***exec_command, int *fds_size)
{
	int i;
	int fd;

	i = 0;
	fd = 0;
	while (command[i] && !ft_strchr(command[i], '>')
		&& !ft_strchr(command[i], '<'))
		i++;
	if (!(*exec_command = (char **)malloc(sizeof(char *) *
		(count_args_redir(command, i) + 1))))
		return (0);
	if (!(*fds = (int *)malloc(sizeof(int) *
		(*fds_size = count_elem_redir(command, i)))))
		return (0);
	fill_arrays(command, fds, exec_command);
	return (0);
}

void	fd_redir(char **command, int *i)
{
	(void)command;
	(void)i;
}


void	file_redir(char **command,int *i, int *fds)
{
	(void)command;
	(void)i;
	(void)fds;
}

int		redirect_fds(char **command, int *fds)
{
	int i;
	int fds_index;

	i = 0;
	while (command[i] && !ft_strchr(command[i], '>')
		&& !ft_strchr(command[i], '<'))
		i++;
	while (command[i])
	{
		printf("\e[31mJe regarde %s\n\e[0m", command[i]);
		if ((ft_strchr(command[i], '>') || ft_strchr(command[i], '<'))
		&& ft_strchr(command[i], '&'))
			fd_redir(command, &i);
		else if (ft_strchr(command[i], '>') || ft_strchr(command[i], '<'))
			file_redir(command, &i, fds);
		i++;
	}
	return (0);
}

char	*recompact_command(char **tab)
{
	int		i;
	int		e;
	char	*ret;

	i = 0;
	e = 0;
	while (tab[e + 1])
		i += ft_strlen(tab[e++]) + 1;
	i += ft_strlen(tab[e]);
	dprintf(2, "J'alloue de %d\n", i);
	if (!(ret = ft_strnew(i)))
		return (NULL);
	e = 0;
	while (tab[e + 1])
	{
		ft_strcat(ret, tab[e++]);
		ft_strcat(ret, " ");
	}
	ft_strcat(ret, tab[e]);
	dprintf(2, "Ma chaine convertit vaut |%s|\n", ret);
	return (ret);
}

int		launch_arrow(t_hustru *big_struc, char **command)
{
	int		*fds;
	char	**exec_command;
	int		fds_size;
	pid_t	pid;


	(void)big_struc;
	if (init_arrays(command, &fds, &exec_command, &fds_size) == -1)
		return (display_error("ymarsh: error in init in redirections\n", NULL));

	int m = 0;
	while (exec_command[m])
		printf("Command = %s\n", exec_command[m++]);
	m = 0;
	while (m != fds_size)
		printf("fds = %d\n", fds[m++]);
	
	if ((pid = fork()) < 0)
		return (display_error("ymarsh: error: fork failed\n", NULL));
	if (!pid)
	{
		if (redirect_fds(command, fds) == 1)
			return (1);
		big_struc->line = recompact_command(exec_command);
		decide_commande(big_struc, exec_command, exec_without_fork);
		close_pipe(fds, fds_size);
	}
	wait(&pid);
	free(exec_command);
	ft_deltab(command);
	return (0);
}
