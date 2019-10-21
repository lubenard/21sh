/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_files.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <lubenard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/20 22:11:28 by lubenard          #+#    #+#             */
/*   Updated: 2019/10/21 16:31:12 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh21.h>

void	pass_heredoc(char **command, int *i)
{
	(*i)++;
	while (command[*i] && (!ft_strchr(command[*i], '>')
	|| (!ft_strchr(command[*i], '<') && ft_occur(command[*i], '<') >= 2)))
		(*i)++;
	(*i)--;
}

int		file_redir(t_hustru *big_struc, char **command, int *i, int *fds)
{
	int		fd;
	int		fd2;

	fd = 0;
	if (!ft_strcmp(command[*i], "&>"))
	{
		fd2 = dup(fds[big_struc->fds_index]);
		dup2(fd2, 2);
	}
	if (ft_strstr(command[*i], "<<"))
		pass_heredoc(command, i);
	else
	{
		if (ft_strchr(command[*i], '>'))
			fd = extract_first_fd(command, *i, extract_first(command[*i], '>'));
		else if (ft_strchr(command[*i], '<'))
			fd = extract_first_fd(command, *i, extract_first(command[*i], '<'));
		dup2(fds[big_struc->fds_index++], fd);
	}
	return (0);
}
