/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   left_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/17 15:59:55 by lubenard          #+#    #+#             */
/*   Updated: 2019/09/30 18:05:47 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh21.h>

/*
** Send into input programm
*/

int		redir_left(char **command, int i)
{
	int file;
	int fd;
	int fd2;

	while (command[i])
	{
		printf("Je regarde %s\n", command[i]);
			if (ft_isdigit(command[i][0]))
				fd = extract_first_fd(command, i, extract_first(command[i], '<'));
			if (command[i][ft_strlen(command[i]) - 1] == '-')
			{
				printf("je ferme mon fd %d\n", fd);
				if (close(fd) == -1)
					return (display_error("ymarsh: Error while closing file\n", NULL));
					if  (command[i + 1] && !ft_strchr(command[i + 1], '<'))
					{
						i++;
						printf("J'ouvre %s\n", command[i]);
						file = open(command[i], O_RDONLY);
						printf("dup2(%d, %d)\n", file, fd);
						dup2(file, fd);
					}
					i++;
			}
			else if (ft_isdigit(command[i][ft_strlen(command[i]) - 1])
	&& command[i][ft_strlen(command[i]) - 2] == '&')
			{
				fd2 = extract_first_fd(command, i, extract_last(command[i], '&'));
				printf("je dup2(%d, %d)\n", fd2, fd);
				dup2(fd2, fd);
				i++;
			}
			else
			{
				printf("Je rentre ici\n");
				if (ft_occur(command[i], '<') == 1)
				{
					i++;
					printf("J'ouvre %s\n", command[i]);
					file = open(command[i], O_RDONLY);
					printf("dup2(%d, %d)\n", file, fd);
					dup2(file, fd);
					while (command[i] && !ft_strchr(command[i], '<'))
					{
						printf("je passe %s\n", command[i]);
						i++;
					}
				}
		}
	}
	return (0);
}

