/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   right_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/17 16:00:39 by lubenard          #+#    #+#             */
/*   Updated: 2019/09/26 20:52:01 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh21.h>

/*
** Have to rewrite the redir: here is how it works
** 1) create files
** 2) execute the command and save output
** 3) fill the files
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

int		prep_redir(t_hustru *big_struc, char **command, char **tab, int i)
{
	int file;
	pid_t pid;
	int fd;
	char *tmp;
	int fd2;

	if ((pid = fork()) < 0)
		return (display_error("ymarsh: error: fork failed", NULL));
	if (!pid)
	{
		//printf("je suis sur %s\n", command[i]);
		while (command[i])
		{
		//	printf("Je regarde %s\n", command[i]);
			if (!ft_strcmp(command[i], ">"))
			{
				i++;
				printf("je rentre dans >\n");
				while (command[i] && !ft_strchr(command[i], '>'))
				{
		//			printf("J'ouvre %s\n", command[i]);
					file = open(command[i++], O_WRONLY | O_TRUNC);
					dup2(file, 1);
				}
			}
			else if (!ft_strcmp(command[i], ">>"))
			{
				i++;
				printf("je rentre dans >>\n");
				while (command[i] && !ft_strchr(command[i], '>'))
				{
		//			printf("J'ouvre %s\n", command[i]);
					file = open(command[i++], O_WRONLY | O_APPEND);
					dup2(file, 1);
				}
			}
			else if (!ft_strcmp(command[i], "&>"))
			{
				i++;
				printf("je rentre dans &>\n");
				while (command[i] && !ft_strchr(command[i], '>'))
				{
					printf("J'ouvre %s\n", command[i]);
					fd2 = open(command[i], O_WRONLY | O_TRUNC);
					file = open(command[i], O_WRONLY | O_TRUNC);
					dup2(fd2, 2);
					dup2(file, 1);
					i++;
				}
			}
			else if (ft_strchr(command[i], '>'))
			{
				if (ft_isdigit(command[i][0]))
				{
					tmp = extract_first(command[i], '>');
					fd = ft_atoi(tmp);
					free(tmp);
				}
		//		printf("%d\n", fd);
				if (command[i][ft_strlen(command[i]) - 1] == '-')
				{
		//			printf("je ferme mon fd %d\n", fd);
					close(fd);
				}
				else if (ft_isdigit(command[i][ft_strlen(command[i]) - 1]) && command[i][ft_strlen(command[i]) - 2] == '&')
				{
					tmp = extract_last(command[i], '&');
					fd2 = ft_atoi(tmp);
		//			printf("The last fd is %d\n", fd2);
		//			printf("je dup2(%d, %d)\n", fd2, fd);
					dup2(fd2, fd);
				}
				else
				{
					printf("Je rentre ici\n");
					if (ft_occur(command[i], '>') == 1)
					{
						i++;
						printf("Je duplique %d\n", fd);
						while (command[i] && !ft_strchr(command[i], '>'))
						{
							printf("J'ouvre %s\n", command[i]);
							file = open(command[i++], O_WRONLY | O_TRUNC);
							dup2(file, fd);
						}
					}
					else if (ft_occur(command[i], '>') == 2)
					{
						i++;
						printf("Je duplique %d\n", fd);
						while (command[i] && !ft_strchr(command[i], '>'))
						{
		//					printf("J'ouvre %s\n", command[i]);
							file = open(command[i++], O_WRONLY | O_APPEND);
							dup2(file, fd);
						}
					}
				}
				i++;
			}
		}
		//printf("J'exec une fois\n");
		exec_without_fork(big_struc, tab);
		exit(0);
	}
	return (0);
}

int		link_files_and_exec(t_hustru *big_struc, char **command, int i)
{
	char	**tab;
	int		e;

	e = 0;
	if (!(tab = (char **)malloc(sizeof(char *) * (i + 1))))
		return (0);
	while (command[e] && !ft_strchr(command[e], '>'))
	{
		tab[e] = command[e];
		e++;
	}
	tab[e] = NULL;
	return (prep_redir(big_struc, command, tab, i));
}

int		create_file(char **filenames, int i)
{
	int file;

	while (filenames[i])
	{
		if (access(filenames[i], F_OK) == -1 && !ft_strchr(filenames[i], '>'))
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
			|| ft_occur(command[i], '>') == 0))
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
