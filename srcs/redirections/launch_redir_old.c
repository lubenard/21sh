/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_redir_old.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/17 16:00:39 by lubenard          #+#    #+#             */
/*   Updated: 2019/10/07 14:55:36 by lubenard         ###   ########.fr       */
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
	dprintf(2, "J'ouvre %s\n", command[*i]);
	if (!flag)
		file = open(command[*i], O_WRONLY | O_TRUNC);
	else if (flag == 1)
		file = open(command[*i], O_WRONLY | O_APPEND);
	else
		file = open(command[*i], O_RDONLY);
	dprintf(2, "dup2(%d, %d)\n", file, fd);
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

int		prep_redir3(char **command, int *i, int fd)
{
	if (ft_occur(command[*i], '>') == 1)
		make_good_redir(command, i, 0, fd);
	else if (ft_occur(command[*i], '>') == 2)
		make_good_redir(command, i, 1, fd);
	return (0);
}

int		prep_redir2(char **command, int *i)
{
	int fd
	int fd2;

	fd = -1;
	if (ft_strchr(command[*i], '>'))
		fd = extract_first_fd(command, *i, extract_first(command[*i], '>'));
	else if (ft_strchr(command[*i], '<'))
		fd = extract_first_fd(command, *i, extract_first(command[*i], '<'));
	dprintf(2, "J'extrais %d\n", fd);
	printf("Mon dernier charactere est %c\n", command[*i][ft_strlen(command[*i]) -1]);
	if (command[*i][ft_strlen(command[*i]) - 1] == '-')
	{
		dprintf(2, "je ferme fd %d\n", fd);
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
		prep_redir3(command, i, fd);
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

void	close_redir(int *fds)
{
	close(fds[1]);
	if (fds[0] != -1)
		close(fds[0]);
	if (fds[2] != -1)
		close(fds[2]);
}

/*
** order of fd inside array
** fds[0] = fd_in;
** fds[1] = fd;
** fds[2] = fd2;
*/

int		loop_redir(char **command, int i, int *fds)
{
	while (command[i])
	{
		printf("\e[31mJe regarde %s\n\e[0m", command[i]);
		if (!ft_strcmp(command[i], ">"))
			fds[1] = make_good_redir(command, &i, 0, 1);
		else if (!ft_strcmp(command[i], ">>"))
			fds[0] = make_good_redir(command, &i, 1, 1);
		else if (!ft_strcmp(command[i], "<"))
			fds[1] = make_good_redir(command, &i, 2, 0);
		else if (!ft_strcmp(command[i], "&>"))
		{
			fds[2] = open(command[i + 1], O_WRONLY | O_TRUNC);
			dup2(fds[2], 2);
			fds[1] = make_good_redir(command, &i, 0, 1);
		}
		else if (ft_strchr(command[i], '>') || ft_strchr(command[i], '<'))
		{
			prep_redir2(command, &i);
			dprintf(2, "retour prep2 = %s\n", command[i]);
		}
		if (fds[1] == -1)
		{
			dprintf(2, "je retourne -1\n");
			return (1);
		}
		dprintf(2, "je boucle \n");
	}
	return (0);
}

int		prep_redir(t_hustru *big_struc, char **command, char **tab, int i)
{
	pid_t	pid;
	int		fds[3];

	fds[2] = -1;
	fds[0] = -1;
	if ((pid = fork()) < 0)
		return (display_error("ymarsh: error: fork failed\n", NULL));
	if (!pid)
	{
		if (loop_redir(command, i, fds) == 1)
			return (1);
		big_struc->line = recompact_command(tab);
		dprintf(2, "cat return %d\n", decide_commande(big_struc, tab, exec_without_fork));
		close_redir(fds);
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
		tab[e++] = ft_strdup(command[j]);
		free(command[j]);
		command[j++] = ft_strdup("");
	}
	j++;
	while (command[j])
	{
		printf("je suis sur %s\n", command[j]);
		if (!ft_strchr(command[j], '>')
		&& !ft_strchr(command[j], '<'))
		{
			if ((ft_strchr(command[j - 1], '>')
			|| ft_strchr(command[j - 1], '<'))
			&& ft_strchr(command[j - 1], '&'))
			{
				tab[e++] = ft_strdup(command[j]);
				free(command[j]);
				command[j] = ft_strdup("");
			}
			else if (!ft_strchr(command[j - 1], '>')
			&& !ft_strchr(command[j - 1], '<'))
			{
				tab[e++] = ft_strdup(command[j]);
				free(command[j]);
				command[j] = ft_strdup("");
			}
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

char	**modify_command(char **command)
{
	int i;
	char **ret;
	int		e;

	i = 0;
	e = 0;
	if (!(ret = (char **)malloc(sizeof(char *) * (ft_tablen(command) + 1))))
		return (NULL);
	while (command[i])
	{
		if (ft_strcmp(command[i], ""))
		{
			ret[e++] = ft_strdup(command[i]);
			free(command[i]);
		}
		i++;
	}
	free(command);
	return (ret);
}

int		launch_arrow(t_hustru *big_struc, char **command)
{
	int		i;
	char	**tab;

	(void)big_struc;
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
	int m = 0;
	while (tab[m])
		printf("tab[m] = %s\n", tab[m++]);
	m = 0;
	while (command[m])
		printf("command = |%s|\n", command[m++]);
	command = modify_command(command);
	m = 0;
	while (command[m])
		printf("command APRES = |%s|\n", command[m++]);
	//if (open_file(command, i))
	return (prep_redir(big_struc, command, tab, i));
	return (0);
}
