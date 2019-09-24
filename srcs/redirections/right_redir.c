/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   right_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/17 16:00:39 by lubenard          #+#    #+#             */
/*   Updated: 2019/09/24 17:54:52 by lubenard         ###   ########.fr       */
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
/*
** ----------------------New redirections ------------------
*/

int		fill_file2(char **command, char **output, int len, int mode)
{
	int file;

	while (command[len] && !ft_strchr(command[len], '>'))
	{
		printf("Je vais fill %s\n", command[len]);
		if (mode == 1)
			file = open(command[len], O_WRONLY | O_TRUNC);
		else if (mode == 2)
			file = open(command[len], O_WRONLY | O_APPEND);
		write(file, output[0], ft_strlen(output[0]));
		len++;
	}
	return (0);
}

int		fill_file(char **command, char **output, int i)
{
	int len;
	//int save;
	//int file;

	(void)output;
	len = ft_tablen(command) - 1;
	while (len != i)
	{
		if (ft_strchr(command[len], '>'))
		{}
		else
		{
			while (command[len] && !ft_strchr(command[len], '>'))
			{
				printf("Je recule sur %s\n", command[len]);
				len--;
			}
			printf("Je suis donc sur %s\n", command[len]);
			if (!ft_strcmp(command[len], ">"))
				fill_file2(command, output, len + 1, 1);
			if (!ft_strcmp(command[len], ">>"))
				fill_file2(command, output, len + 1, 2);
			//printf("J'ouvre %s\n", command[len]);
			//file = open(command[len], O_WRONLY | O_TRUNC);
		}
	}
	return (0);
}

char	**exec_command_redir(t_hustru *big_struc, char **argv)
{
	int		link[4];
	pid_t	pid;
	char	output_std[50000];
	char	output_err[50000];
	char	**tab;

	if (!(tab = (char **)malloc(sizeof(char *) * 2))
		|| pipe(link) < 0 || pipe(link + 2) < 0 || (pid = fork()) < 0)
		return (NULL);
	if (pid == 0)
	{
		dup2(link[1], 1);
		dup2(link[3], 2);
		close_pipe(link, 4);
		exit(basic_command(big_struc, argv));
	}
	else
	{
		wait(&pid);
		close(link[1]);
		close(link[3]);
		read(link[0], output_std, 50000);
		read(link[2], output_err, 50000);
	}
	printf("------------------start-------------------------\n");
	printf("[Exec redir] output_std vaut %s\n", output_std);
	printf("[Exec redir] output_err vaut %s\n", output_err);
	printf("-------------------end-----------------------\n");
	tab[0] = ft_strndup(output_std, ft_strlen(output_std) - 1);
	tab[1] = ft_strndup(output_err, ft_strlen(output_err) - 1);
	return (tab);
}

int		prepare_command_redir(t_hustru *big_struc, char **command, int i)
{
	char	**output;
	char	**tab;
	int		e;

	e = 0;
	if (!(tab = (char **)malloc(sizeof(char *) * (i + 1))))
		return (0);
	while (e != i)
	{
		tab[e] = command[e];
		e++;
	}
	tab[e] = NULL;
	output = exec_command_redir(big_struc, tab);
	fill_file(command, output, i);
	return (0);
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
		i++;
	}
	return (0);
}

int		link_files(char **command, int i)
{
	int e;
	int file;

	e = 0;
	printf("Avant de boucler je suis sur %s\n", command[i]);
	while (command[i])
	{
		printf("[link_file] Je boucle\n");
		if (!ft_strcmp(command[i], ">"))
		{
			printf("Je vais faire une redir sur >\n");
			i++;
			while (command[i] && !ft_strchr(command[i], '>'))
			{
				printf("J'ouvre %s\n", command[i]);
				file = open(command[i], O_WRONLY | O_TRUNC);
				printf("Je dup2(%d, 1)\n", file);
				dup2(file, 1);
				i++;
			}
		}
		else if (!ft_strcmp(command[i], "2>"))
		{
			printf("Je vais faire une redir sur 2>\n");
			i++;
			while (command[i] && !ft_strchr(command[i], '>'))
			{
				printf("J'ouvre %s\n", command[i]);
				file = open(command[i], O_WRONLY | O_TRUNC);
				printf("Je dup2(%d, 1)\n", file);
				dup2(file, 2);
				i++;
			}
		}
	}
	file = -1;
	return (file);
}

int		arrow_right(t_hustru *big_struc, char **command)
{
	int e = 0;

	if (check_redir(command))
		return (1);
	while (!ft_strchr(command[e], '>'))
		e++;
	create_file(command, e + 1);
	//tmp = link_files(command, e);
	printf("je lance la commande\n");
	prepare_command_redir(big_struc, command, e);
	return (0);
}
