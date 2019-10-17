/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_redir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <lubenard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 01:56:26 by lubenard          #+#    #+#             */
/*   Updated: 2019/10/17 22:11:10 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh21.h>

/*
** Have to rewrite the redir: here is how it works
** 1) create files
** 2) Make the god redirections
** 3) Execute the command
*/

int		is_command_redir(int **fds, char **command, int j, int *k)
{
	int fd;

	if (access(command[j], F_OK) == -1 && ft_strcmp(command[j - 1], "<<"))
	{
		if ((fd = open(command[j], O_CREAT, 0644) < 0))
			return (display_error("ymarsh: error while creating file ",
			command[j]));
	}
	if ((ft_strstr(command[j - 1], "&>")
	|| ft_strchr(command[j - 1], '>')
	|| ft_strchr(command[j - 1], '<'))
	&& !ft_strstr(command[j - 1], ">&")
	&& !ft_strstr(command[j - 1], "<&")
	&& ft_strcmp(command[j - 1], "<<"))
	{
		//printf("[Fill fds tab] Je rajoute %s\n", command[j]);
		if (ft_occur(command[j - 1], '>') == 1)
			(*fds)[(*k)++] = open(command[j], O_WRONLY | O_TRUNC);
		else if (ft_occur(command[j - 1], '>') == 2)
			(*fds)[(*k)++] = open(command[j], O_WRONLY | O_APPEND);
		else if (ft_strchr(command[j - 1], '<'))
			(*fds)[(*k)++] = open(command[j], O_RDONLY);
		//printf("J'ai ouvert %s et sont fd associe est %d\n", command[j], (*fds)[(*k) - 1]);
	}
	else if (ft_strchr(command[j - 1], '>') && ft_strchr(command[j - 1], '<'))
	{
		if (ft_occur(command[j - 1], '>') == 1)
			(*fds)[(*k)++] = open(command[j], O_WRONLY | O_TRUNC);
		else if (ft_occur(command[j - 1], '>') == 2)
			(*fds)[(*k)++] = open(command[j], O_WRONLY | O_APPEND);
		else if (ft_strchr(command[j - 1], '<'))
			(*fds)[(*k)++] = open(command[j], O_RDONLY);
	}
	return (0);
}

int		is_command(char ***exec_command, char **command, int j, int *i)
{
	if (j > 0)
	{
		if ((ft_strstr(command[j - 1], "<&")
		|| ft_strstr(command[j - 1], ">&")) && is_digit(command[j - 1]))
		{
			//printf("[Adding to command] Je rajoute %s\n", command[j]);
			(*exec_command)[(*i)++] = command[j];
			return (1);
		}
		else if (!ft_strchr(command[j - 1], '>')
		&& !ft_strchr(command[j - 1], '<'))
		{
			//printf("[Count args redir] Je rajoute %s\n", command[j]);
			(*exec_command)[(*i)++] = command[j];
			return (1);
		}
	}
	else
	{
		//printf("[Adding to command] Je rajoute %s\n", command[j]);
		(*exec_command)[(*i)++] = command[j];
		return (1);
	}
	return (0);
}

int		is_heredoc(char **command, int j, int mode)
{
	(void)mode;
	//printf("command[j - 1] = %s\n", command[j]);
	if (command[j])
	{
		if (!ft_strcmp(command[j], "<<"))
		{
			//printf("Je retourne 0\n");
			return (0);
		}
	}
	//printf("Je retourne 1\n");
	return (1);
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
		//printf("[filling] Je regarde %s\n", command[j]);
		if ((!ft_strchr(command[j], '>') && !ft_strchr(command[j], '<'))
		|| is_between_quotes(command[j], 3))
		{
			if (!is_command(exec_command, command, j, &i))
			{
				//printf("Je rentre dans commad_redir\n");
				is_command_redir(fds, command, j, &k);
			}
		}
		j++;
	}
	(*exec_command)[i] = NULL;
	return (0);
}

int		init_arrays(char **command, int **fds,
	char ***exec_command, int *fds_size)
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
		return (display_error("ymarsh: error during malloc", NULL));
	if (!(*fds = (int *)malloc(sizeof(int) *
		(*fds_size = count_elem_redir(command, i)))))
		return (display_error("ymarsh: error during malloc", NULL));
	return (fill_arrays(command, fds, exec_command));
}

int		extract_first_fd(char **command, int i, char *to_convert)
{
	int		fd;

	fd = 0;
	if (ft_isdigit(command[i][0]))
	{
		fd = ft_atoi(to_convert);
		free(to_convert);
		//printf("J'extrais %d\n", fd);
	}
	else
	{
		if (ft_strchr(command[i], '>'))
			fd = 1;
		else if (ft_strchr(command[i], '<'))
			fd = 0;
	}
	return (fd);
}

void	fd_redir(char **command, int *i)
{
	int		fd;
	int		fd2;
	char	last_char;

	fd = 0;
	//printf("FD_REDIR\n");
	if (ft_strchr(command[*i], '>'))
		fd = extract_first_fd(command, *i, extract_first(command[*i], '>'));
	else if (ft_strchr(command[*i], '<'))
		fd = extract_first_fd(command, *i, extract_first(command[*i], '<'));
	//printf("First fd is %d\n", fd);
	last_char = command[*i][ft_strlen(command[*i]) - 1];
	//printf("Mon last char est |%c|\n", last_char);
	if (last_char == '-')
	{
	//	printf("Je ferme %d\n", fd);
		if (close(fd) == -1)
			display_error("ymarsh: Error while closing file\n", NULL);
	}
	else if (ft_isdigit(last_char))
	{
		fd2 = extract_first_fd(command, *i, extract_last(command[*i], '&'));
		//printf("je redirige %d -> %d\n", fd, fd2);
		dup2(fd2, fd);
	}
}

int		do_heredoc(t_hustru *big_struc, char **command, int *i)
{
	//faire un pipe
	int link[2];

	if (pipe(link) == -1)
		return (0);

	//printf("OULALA %s\n", heredoc(big_struc, command));
	ft_putstr_fd(heredoc(big_struc, command), link[1]);
	close(link[1]);
	dup2(link[0], 0);
	//close(link[0]);
	(void)i;
	/*(*i)++;
	while (command[*i] && !ft_strchr(command[*i], '>') || (!))
	{
		(*i)++;
	}
	(*i)--;*/
	return (0);
}

int		file_redir(t_hustru *big_struc, char **command, int *i, int *fds)
{
	int		fd;
	int		fd2;

	fd = 0;
	//printf("FILE_REDIR\n");
	if (!ft_strcmp(command[*i], "&>"))
	{
	//	printf("doucle redir\n");
		fd2 = dup(fds[big_struc->fds_index]);
	//	printf("Je redirige %d vers %d\n", 2, fd2);
		dup2(fd2, 2);
	}
	if (ft_strstr(command[*i], "<<"))
	{
		(*i)++;
		while (command[*i] && (!ft_strchr(command[*i], '>') || (!ft_strchr(command[*i], '<') && ft_occur(command[*i], '<') >= 2)))
		{
			//printf("Je passe %s\n", command[*i]);
			(*i)++;
		}
		(*i)--;
		//do_heredoc(big_struc, command, i);
	}
	else
	{
		if (ft_strchr(command[*i], '>'))
			fd = extract_first_fd(command, *i, extract_first(command[*i], '>'));
		else if (ft_strchr(command[*i], '<'))
			fd = extract_first_fd(command, *i, extract_first(command[*i], '<'));
		//printf("Extracted fd = %d\n", fd);
		//printf("je redirige %d -> %d\n", fd, fds[big_struc->fds_index]);
		dup2(fds[big_struc->fds_index++], fd);
	}
	return (0);
}

int		redirect_fds(t_hustru *big_struc, char **command, int *fds)
{
	int i;

	i = 0;
	big_struc->fds_index = 0;
	while (command[i] && !ft_strchr(command[i], '>')
		&& !ft_strchr(command[i], '<'))
		i++;
	if (ft_tabstr(command, "<<"))
		do_heredoc(big_struc, command, &i);
	while (command[i])
	{
		//printf("\e[31mJe regarde %s\n\e[0m", command[i]);
		if ((ft_strchr(command[i], '>') || ft_strchr(command[i], '<'))
		&& ft_strchr(command[i], '&') && ft_strcmp(command[i], "&>"))
			fd_redir(command, &i);
		else if (ft_strchr(command[i], '>') || ft_strchr(command[i], '<')
		|| !ft_strcmp(command[i], "&>"))
			file_redir(big_struc, command, &i, fds);
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
	/*int debug = 0;
	while (tab[debug])
		printf("tab recompact command = %s\n", tab[debug++]);*/
	while (tab[e + 1])
		i += ft_strlen(tab[e++]) + 1;
	i += ft_strlen(tab[e]);
	//dprintf(2, "J'alloue de %d\n", i);
	if (!(ret = ft_strnew(i)))
		return (NULL);
	e = 0;
	while (tab[e + 1])
	{
		ft_strcat(ret, tab[e++]);
		ft_strcat(ret, " ");
	}
	ft_strcat(ret, tab[e]);
	//dprintf(2, "Ma chaine convertit vaut |%s|\n", ret);
	return (ret);
}

int		launch_arrow_w_fork(t_hustru *big_struc, char **command)
{
	int		*fds;
	char	**exec_command;
	int		fds_size;
	pid_t	pid;
	int		tmp_fd;

	tmp_fd = 0;
	pid = 0;
	/*int m;
	m = 0;
	while (command[m])
		printf("Je recois %s\n", command[m++]);*/
	if (init_arrays(command, &fds, &exec_command, &fds_size) == -1)
		return (display_error("ymarsh: init failed in redirections\n", NULL));
	tmp_fd = redirect_fds(big_struc, command, fds);
	//int jj = 0;
	//while (exec_command[jj])
	//	printf("Tab d'exec = %s\n", exec_command[jj++]);
	decide_commande(big_struc, exec_command, exec_without_fork, 0);
	free(fds);
	free(exec_command);
	if (tmp_fd > 0)
		close(tmp_fd);
	return (0);
}

int		launch_arrow(t_hustru *big_struc, char **command)
{
	int		*fds;
	char	**exec_command;
	int		fds_size;
	pid_t	pid;
	int		tmp_fd;

	tmp_fd = 0;
	pid = 0;
	/*int m = 0;
	while (command[m])
		printf("Je recois %s\n", command[m++]);*/
	if (init_arrays(command, &fds, &exec_command, &fds_size) == -1)
		return (display_error("ymarsh: init failed in redirections\n", NULL));
	if (!is_valid_command(big_struc, command) && (pid = fork()) >= 0)
	{
		if (!pid)
		{
			tmp_fd = redirect_fds(big_struc, command, fds);
			/*int jj = 0;
			while (exec_command[jj])
				printf("Tab d'exec = %s\n", exec_command[jj++]);
			while (jj < fds_size)
				printf("Tab d'exec_fds = %d\n", fds[jj++]);*/
			decide_commande(big_struc, exec_command, exec_without_fork, 0);
			exit(0);
		}
		wait(&pid);
	}
	free(fds);
	free(exec_command);
	if (tmp_fd > 0)
		close(tmp_fd);
	return (0);
}
