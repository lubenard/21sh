/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   left_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/17 15:59:55 by lubenard          #+#    #+#             */
/*   Updated: 2019/09/30 16:38:32 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh21.h>

/*
** Send into input programm
*/

int		redir_left(char **command, int i)
{
	int file;
	int fd;
	int fd2;

	while (command[i])
	{
		printf("Je regarde %s\n", command[i]);
		if (!ft_strcmp(command[i], "<"))
		{
			i++;
			file = open(command[i], O_RDONLY);
			printf("Je duplique %s (file descriptor %d)\n", command[i], file);
			dup2(file, 0);
			while (command[i] && !ft_strchr(command[i], '<'))
				i++;
		}
		else
		{
			if (ft_isdigit(command[i][0]))
				fd = extract_first_fd(command, i, extract_first(command[i], '<'));
			if (command[i][ft_strlen(command[i]) - 1] == '-')
			{
				printf("je ferme mon fd %d\n", fd);
				if (close(fd) == -1)
					return (display_error("ymarsh: Error while closing file\n", NULL));
					if  (command[i + 1] && !ft_strchr(command[i + 1], '<'))
					{
						i++;
						printf("J'ouvre %s\n", command[i]);
						file = open(command[i], O_RDONLY);
						printf("dup2(%d, %d)\n", file, fd);
						dup2(file, fd);
					}
					i++;
			}
			else if (ft_isdigit(command[i][ft_strlen(command[i]) - 1])
	&& command[i][ft_strlen(command[i]) - 2] == '&')
			{
				fd2 = extract_first_fd(command, i, extract_last(command[i], '&'));
				printf("je dup2(%d, %d)\n", fd2, fd);
				dup2(fd2, fd);
				i++;
			}
			else
			{
				printf("Je rentre ici\n");
				if (ft_occur(command[i], '<') == 1)
				{
					i++;
					printf("J'ouvre %s\n", command[i]);
					file = open(command[i], O_RDONLY);
					printf("dup2(%d, %d)\n", file, fd);
					dup2(file, fd);
					while (command[i] && !ft_strchr(command[i], '<'))
					{
						printf("je passe %s\n", command[i]);
						i++;
					}
				}
			}
		}
	}
	return (0);
}

int		exec_left(t_hustru *big_struc, char **command, char **tab)
{
	pid_t pid;

	(void)command;
	if ((pid = fork()) < 0)
		return (display_error("ymarsh: error: fork failed\n", NULL));
	if (!pid)
	{
		printf("J'execute %s\n", tab[0]);
		basic_command(big_struc, tab, exec_without_fork);
		exit(0);
	}
	wait(&pid);
	free(tab);
	return (0);
}

int		arrow_left(t_hustru *big_struc, char **command)
{
	int i;
	char	**tab;

	(void)big_struc;
	i = 0;
	while (command[i] && !ft_strchr(command[i], '<'))
		i++;
	if (!(tab = create_command(command, i, '<')))
		return (1);
	redir_left(command, i);
	exec_left(big_struc, command, tab);
	ft_deltab(command);
	return (0);
}
