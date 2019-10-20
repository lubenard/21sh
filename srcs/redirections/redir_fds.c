/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_fds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <lubenard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/20 22:07:57 by lubenard          #+#    #+#             */
/*   Updated: 2019/10/20 22:19:53 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh21.h>

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
