/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_redir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <lubenard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 01:56:26 by lubenard          #+#    #+#             */
/*   Updated: 2019/10/21 12:29:06 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh21.h>

/*
** Have to rewrite the redir: here is how it works
** 1) create files
** 2) Make the god redirections
** 3) Execute the command
*/

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

int		do_heredoc(t_hustru *big_struc, char **command)
{
	//faire un pipe
	int link[2];

	if (pipe(link) == -1)
		return (0);
	ft_putstr_fd(heredoc(big_struc, command), link[1]);
	close(link[1]);
	dup2(link[0], 0);
	return (0);
}

int		redirect_fds(t_hustru *big_struc, char **command, int *fds, int fds_size)
{
	int i;

	i = 0;
	big_struc->fds_index = 0;
	while (command[i] && !ft_strchr(command[i], '>')
		&& !ft_strchr(command[i], '<'))
		i++;
	if (ft_tabstr(command, "<<") && big_struc->should_heredoc == 1)
	{
		//printf("je lance heredoc\n");
		do_heredoc(big_struc, command);
	}
	while (command[i])
	{
		//printf("\e[31mJe regarde %s\n\e[0m", command[i]);
		if ((ft_strchr(command[i], '>') || ft_strchr(command[i], '<'))
		&& ft_strchr(command[i], '&') && ft_strcmp(command[i], "&>"))
			fd_redir(command, &i);
		else if ((ft_strchr(command[i], '>') || ft_strchr(command[i], '<')
		|| !ft_strcmp(command[i], "&>")) && big_struc->fds_index < fds_size)
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
	tmp_fd = redirect_fds(big_struc, command, fds, fds_size);
	int jj = 0;
	while (exec_command[jj])
		printf("Tab d'exec = %s\n", exec_command[jj++]);
	decide_commande(big_struc, exec_command, exec_without_fork, 0);
	if (tmp_fd > 0)
		close(tmp_fd);
	tmp_fd = 0;
	while (tmp_fd < fds_size)
		close(fds[tmp_fd++]);
	free(fds);
	free(exec_command);
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
	int m = 0;
	while (command[m])
		printf("Je recois %s\n", command[m++]);
	if (init_arrays(command, &fds, &exec_command, &fds_size) == -1)
		return (display_error("ymarsh: init failed in redirections\n", NULL));
	if (!is_valid_command(big_struc, command) && (pid = fork()) >= 0)
	{
		if (!pid)
		{
			tmp_fd = redirect_fds(big_struc, command, fds, fds_size);
			int jj = 0;
			while (exec_command[jj])
				printf("Tab d'exec = %s\n", exec_command[jj++]);
			/*while (jj < fds_size)
				printf("Tab d'exec_fds = %d\n", fds[jj++]);*/
			decide_commande(big_struc, exec_command, exec_without_fork, 0);
			exit(0);
		}
		wait(&pid);
	}
	if (tmp_fd > 0)
		close(tmp_fd);
	tmp_fd = 0;
	while (tmp_fd < fds_size)
		close(fds[tmp_fd++]);
	free(fds);
	free(exec_command);
	return (0);
}
