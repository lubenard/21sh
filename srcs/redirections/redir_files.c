/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_files.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <lubenard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/20 22:11:28 by lubenard          #+#    #+#             */
/*   Updated: 2019/10/20 22:11:42 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh21.h>

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
		printf("big_struc->fds_index = %d\n", big_struc->fds_index);
		printf("je redirige %d -> %d\n", fd, fds[big_struc->fds_index]);
		dup2(fds[big_struc->fds_index++], fd);
	}
	return (0);
}

