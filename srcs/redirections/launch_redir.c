/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   right_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/17 16:00:39 by lubenard          #+#    #+#             */
/*   Updated: 2019/10/02 15:53:26 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh21.h>

/*
** Have to rewrite the redir: here is how it works
** 1) create files
** 2) Make the god redirections
** 3) Execute the command
*/

int		make_good_redir(char **command, int *i, int flag, int fd)
{
	int file;

	(*i)++;
	printf("J'ouvre %s\n", command[*i]);
	if (!flag)
		file = open(command[*i], O_WRONLY | O_TRUNC);
	else if (flag == 1)
		file = open(command[*i], O_WRONLY | O_APPEND);
	else
		file = open(command[*i], O_RDONLY);
	printf("dup2(%d, %d)\n", file, fd);
	if (file < 0 || fd < 0)
	{
		display_error("ymarsh: file not found: ", command[*i]);
		return (-1);
	}
	else
		dup2(file, fd);
	while (command[*i] && !ft_strchr(command[*i], '>')
	&& !ft_strchr(command[*i], '<'))
	{
		printf("je passe %s\n", command[*i]);
		(*i)++;
	}
	return (file);
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

int		prep_redir2(char **command, int *i)
{
	int fd;
	int fd2;

	if (ft_strchr(command[*i], '>'))
		fd = extract_first_fd(command, *i, extract_first(command[*i], '>'));
	else if (ft_strchr(command[*i], '<'))
		fd = extract_first_fd(command, *i, extract_first(command[*i], '<'));
	if (command[*i][ft_strlen(command[*i]) - 1] == '-')
	{
		printf("je ferme mon fd %d\n", fd);
		if (close(fd) == -1)
			return (display_error("ymarsh: Error while closing file\n", NULL));
		(*i)++;
	}
	else if (ft_isdigit(command[*i][ft_strlen(command[*i]) - 1])
	&& command[*i][ft_strlen(command[*i]) - 2] == '&')
	{
		fd2 = extract_first_fd(command, *i, extract_last(command[*i], '&'));
		printf("je dup2(%d, %d)\n", fd2, fd);
		dup2(fd2, fd);
		(*i)++;
	}
	else
	{
		printf("Je rentre ici\n");
		if (ft_occur(command[*i], '>') == 1)
			make_good_redir(command, i, 0, fd);
		else if (ft_occur(command[*i], '>') == 2)
			make_good_redir(command, i, 1, fd);
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

int		prep_redir(t_hustru *big_struc, char **command, char **tab, int i)
{
	pid_t	pid;
	int		fd2;
	int		fd;
	int		fd_in;

	fd2 = -1;
	fd_in = -1;
	if ((pid = fork()) < 0)
		return (display_error("ymarsh: error: fork failed\n", NULL));
	if (!pid)
	{
		while (command[i])
		{
			printf("\e[31mJe regarde %s\n\e[0m", command[i]);
			if (!ft_strcmp(command[i], ">"))
				fd = make_good_redir(command, &i, 0, 1);
			else if (!ft_strcmp(command[i], ">>"))
				fd_in = make_good_redir(command, &i, 1, 1);
			else if (!ft_strcmp(command[i], "<"))
				fd = make_good_redir(command, &i, 2, 0);
			else if (!ft_strcmp(command[i], "&>"))
			{
				printf("je rentre dans &>\n");
				printf("J'ouvre %s\n", command[i + 1]);
				fd2 = open(command[i + 1], O_WRONLY | O_TRUNC);
				dup2(fd2, 2);
				fd = make_good_redir(command, &i, 0, 1);
			}
			else if (ft_strchr(command[i], '>') || ft_strchr(command[i], '<'))
				prep_redir2(command, &i);
			if (fd == -1)
				return (1);
		}
		dprintf(2, "j'execute %s\n", tab[0]);
		int m = 0; //Used for debug only
		while (tab[m])
			dprintf(2, "Tab = %s\n", tab[m++]);
		big_struc->line = recompact_command(tab);
		decide_commande(big_struc, tab, exec_without_fork);
		printf("Je ferme %d\n", fd);
		close(fd);
		if (fd_in != -1)
			close(fd_in);
		if (fd2 != -1)
			close(fd2);
		exit(0);
	}
	wait(&pid);
	free(tab);
	ft_deltab(command);
	return (0);
}

char	**create_command(char **command, int i)
{
	char	**tab;
	int		e;
	int		j;

	e = 0;
	j = 0;
	if (!(tab = (char **)malloc(sizeof(char *) *
		(count_elem_redir(command, i) + 1))))
		return (0);
	while (e != i)
	{
		printf("[Premiere boucle] Je rajoute %s\n", command[e]);
		tab[e++] = command[j++];
	}
	j += 2;
	while (command[j])
	{
		if (!ft_strchr(command[j], '>')
		&& !ft_strchr(command[j - 1], '>')
		&& !ft_strchr(command[j], '<')
		&& !ft_strchr(command[j - 1], '<'))
		{
			printf("[Seconde boucle] Je rajoute %s\n", command[j]);
			tab[e++] = command[j];
		}
		j++;
	}
	tab[e] = NULL;
	return (tab);
}

int		create_file(char **filenames, int i)
{
	int file;

	while (filenames[i])
	{
		if (access(filenames[i], F_OK) == -1 && !ft_strchr(filenames[i], '>')
			&& ft_strchr(filenames[i - 1], '>'))
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

int		launch_arrow(t_hustru *big_struc, char **command)
{
	int		i;
	char	**tab;

	i = 0;
	if (check_redir(command))
		return (1);
	while (command[i] && !ft_strchr(command[i], '>')
		&& !ft_strchr(command[i], '<'))
		i++;
	if (create_file(command, i) > 0)
		return (1);
	if (!(tab = create_command(command, i)))
		return (1);
	return (prep_redir(big_struc, command, tab, i));
}
