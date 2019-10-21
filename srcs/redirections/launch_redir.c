/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_redir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <lubenard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 01:56:26 by lubenard          #+#    #+#             */
/*   Updated: 2019/10/21 19:41:53 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh21.h>

/*
** here is how redir works
** 1) create files if needed
** 2) Make the god redirections
** 3) Execute the command
** 4) It will automatically fill the files
*/

int		extract_first_fd(char **command, int i, char *to_convert)
{
	int		fd;

	fd = 0;
	if (ft_isdigit(command[i][0]))
	{
		fd = ft_atoi(to_convert);
		free(to_convert);
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

int		redirect_fds(t_hustru *big_struc, char **command,
	int *fds, int fds_size)
{
	int i;

	i = 0;
	big_struc->fds_index = 0;
	while (command[i] && !ft_strchr(command[i], '>')
		&& !ft_strchr(command[i], '<'))
		i++;
	if (ft_tabstr(command, "<<") && big_struc->should_heredoc == 1)
		do_heredoc(big_struc, command);
	while (command[i])
	{
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

void	close_fds(int tmp_fd, int fds_size, int *fds)
{
	if (tmp_fd > 0)
		close(tmp_fd);
	tmp_fd = 0;
	while (tmp_fd < fds_size)
		close(fds[tmp_fd++]);
	free(fds);
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
	if (init_arrays(command, &fds, &exec_command, &fds_size) == -1)
		return (display_error("ymarsh: init failed in redirections\n", NULL));
	tmp_fd = redirect_fds(big_struc, command, fds, fds_size);
	decide_commande(big_struc, exec_command, exec_without_fork, 0);
	close_fds(tmp_fd, fds_size, fds);
	free(exec_command);
	return (0);
}

#include <stdio.h>

int		launch_arrow(t_hustru *big_struc, char **command)
{
	int		*fds;
	char	**exec_command;
	int		fds_size;
	pid_t	pid;
	int		tmp_fd;

	tmp_fd = 0;
	pid = 0;
	if (init_arrays(command, &fds, &exec_command, &fds_size) == -1)
		return (display_error("ymarsh: init failed in redirections\n", NULL));
	if (!is_valid_command(big_struc, command) && (pid = fork()) >= 0)
	{
		if (!pid)
		{
			tmp_fd = redirect_fds(big_struc, command, fds, fds_size);
			decide_commande(big_struc, exec_command, exec_without_fork, 0);
			exit(0);
		}
		printf("Je wait mon pid\n");
		wait(&pid);
		printf("Pid finide wait\n");
	}
	close_fds(tmp_fd, fds_size, fds);
	free(exec_command);
	return (0);
}
