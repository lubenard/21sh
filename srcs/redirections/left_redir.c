/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   left_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/17 15:59:55 by lubenard          #+#    #+#             */
/*   Updated: 2019/08/13 17:28:02 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh21.h>

/*
** Send into input programm
*/

void	double_arrow_left(t_env *lkd_env, char *command)
{
	(void)command;
	(void)lkd_env;
}

void	arrow_left(t_hustru *big_struc, char *command)
{
//	int		input;
	char	**tab;
	int		i = 0;
	pid_t	pid;
	int		fd;

	char *test[2] = {"cat", NULL};
	tab = ft_strsplit(command, ' ');
	while (tab[i])
		printf("command vaut %s\n", tab[i++]);
	pid = fork();
	if (pid == 0)
	{
		fd = open(tab[i-1], O_RDONLY);
		dup2(fd, 0);
		close(fd);
		execve(find_path(big_struc->path, test[0]), test, big_struc->path);
	}
}
