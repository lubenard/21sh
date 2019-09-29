/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   right_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/17 16:00:39 by lubenard          #+#    #+#             */
/*   Updated: 2019/09/29 15:38:53 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh21.h>
#include <errno.h>

/*
** Have to rewrite the redir: here is how it works
** 1) create files
** 2) Make the god redirections
** 3) Execute the command
*/

void	save_redir(char *command, char *content)
{
	char **tab;
	char **filenames;

	(void)command;
	(void)tab;
	(void)filenames;
	(void)content;
	//tab = prepare_tab(command, '>');
	//filenames = save_filename(tab, 1);
	//create_file(filenames, tab);
	////fill_file(filenames, content, tab);
}

int		make_good_redir(char **command, int *i, int flag)
{
	int file;

	(*i)++;
	printf("J'ouvre %s\n", command[*i]);
	if (!flag)
		file = open(command[*i], O_WRONLY | O_TRUNC);
	else
		file = open(command[*i], O_WRONLY | O_APPEND);
	dup2(file, 1);
	while (command[*i] && !ft_strchr(command[*i], '>'))
	{
		printf("je passe %s\n", command[*i]);
		(*i)++;
	}
	return (0);
}

int		extract_first_fd(char **command, int i, char *to_convert)
{
	int		fd;

	if (ft_isdigit(command[i][0]))
	{
		fd = ft_atoi(to_convert);
		free(to_convert);
		printf("J'extrais %d\n", fd);
	}
	else
		fd = 1;
	return (fd);
}

int		prep_redir(t_hustru *big_struc, char **command, char **tab, int i)
{
	pid_t pid;
	int fd;
	int fd2;

	if ((pid = fork()) < 0)
		return (display_error("ymarsh: error: fork failed", NULL));
	if (!pid)
	{
		while (command[i])
		{
			printf("Je regarde %s\n", command[i]);
			if (!ft_strcmp(command[i], ">"))
				make_good_redir(command, &i, 0);
			else if (!ft_strcmp(command[i], ">>"))
				make_good_redir(command, &i, 1);
			else if (!ft_strcmp(command[i], "&>"))
			{
				printf("je rentre dans &>\n");
				printf("J'ouvre %s\n", command[i + 1]);
				fd2 = open(command[i + 1], O_WRONLY | O_TRUNC);
				dup2(fd2, 2);
				make_good_redir(command, &i, 0);
			}
			else if (ft_strchr(command[i], '>'))
			{
				fd = extract_first_fd(command, i, extract_first(command[i], '>'));
				if (command[i][ft_strlen(command[i]) - 1] == '-')
				{
					printf("je ferme mon fd %d\n", fd);
					printf("fcntl renvoie %d\n", fcntl(fd, F_GETFD));
					if (close(fd) == -1)
					{
						dprintf(2, "ERROR NUMBER %d %s\n", errno, strerror(errno));
						return (1);
					}
					i++;
				}
				else if (ft_isdigit(command[i][ft_strlen(command[i]) - 1]) && command[i][ft_strlen(command[i]) - 2] == '&')
				{
					fd2 = extract_first_fd(command, i, extract_last(command[i], '&'));
					printf("je dup2(%d, %d)\n", fd2, fd);
					dup2(fd2, fd);
					i++;
				}
				else
				{
					printf("Je rentre ici\n");
					if (ft_occur(command[i], '>') == 1)
						make_good_redir(command, &i, 0);
					else if (ft_occur(command[i], '>') == 2)
						make_good_redir(command, &i, 0);
				}
			}
		}
		exec_without_fork(big_struc, tab);
		exit(0);
	}
	wait(&pid);
	return (0);
}

int		link_files_and_exec(t_hustru *big_struc, char **command, int i)
{
	char	**tab;
	int		e;
	int		j;

	e = 0;
	j = 0;
	(void)big_struc;
	if (!(tab = (char **)malloc(sizeof(char *) * (count_elem_redir(command, i) + 1))))
		return (0);
	while (e != i)
	{
		printf("[Premiere boucle] Je rajoute %s\n", command[e]);
		tab[e++] = command[j++];
	}
	j += 2;
	while (command[j])
	{
		if (!ft_strchr(command[j], '>') && !ft_strchr(command[j - 1], '>'))
		{
			printf("[Seconde boucle] Je rajoute %s\n", command[j]);
			tab[e++] = command[j];
		}
		j++;
	}
	tab[e] = NULL;
	return (prep_redir(big_struc, command, tab, i));
}

int		create_file(char **filenames, int i)
{
	int file;

	while (filenames[i])
	{
		if (access(filenames[i], F_OK) == -1 && !ft_strchr(filenames[i], '>') && ft_strchr(filenames[i - 1], '>'))
		{
			printf("Je cree %s\n", filenames[i]);
			if ((file = open(filenames[i], O_CREAT, 0666) < 0))
				return (display_error("ymarsh: error while creating file ",
					filenames[i]));
			close(file);
		}
		i++;
	}
	return (0);
}

int		check_redir(char **command)
{
	int		i;
	int		last_char;

	i = 0;
	while (command[i])
	{
		last_char = ft_strlen(command[i]) - 1;
		if (ft_occur(command[i], '>') >= 3)
			return (print_error_redirect(">"));
		else if (!command[i + 1] && command[i][last_char] == '>')
			return (print_error_redirect("\\n"));
		else if (command[i][last_char] == '>'
			&& command[i + 1][0] == '>')
			return (print_error_redirect(command[i + 1]));
		else if (ft_isdigit(command[i][0]) && (ft_occur(command[i], '>') > 1
			|| ft_occur(command[i], '>') == 0)
			&& ft_isdigit(command[i][ft_strlen(command[i]) - 1]))
			return (print_error_redirect("&"));
		i++;
	}
	return (0);
}

int		arrow_right(t_hustru *big_struc, char **command)
{
	int		i;

	i = 0;
	if (check_redir(command))
		return (1);
	while (command[i] && !ft_strchr(command[i], '>'))
		i++;
	if (create_file(command, i) > 0)
		return (1);
	return (link_files_and_exec(big_struc, command, i));
}
