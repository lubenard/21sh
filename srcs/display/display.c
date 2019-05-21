/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/15 15:40:41 by lubenard          #+#    #+#             */
/*   Updated: 2019/05/21 15:19:30 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../sh21.h"

void	display_prompt(char *username, char *curr_dir)
{
	ft_putstr("\033[31m");
	ft_putstr(username);
	ft_putstr("\033[0m - \033[36m");
	ft_putstr(curr_dir);
	ft_putstr("\033[0m >  ");
}

void	invalid_command(char *command)
{
	ft_putstr_fd("Error: ", 2);
	ft_putstr_fd(command, 2);
	ft_putstr_fd(" : command not found ¯\\_(ツ)_/¯\n", 2);
}

int		get_error_exec(char path[6000], int mode)
{
	struct stat filestat;

	if (stat(path, &filestat) < 0)
		return (1);
	if (!(filestat.st_mode & S_IXUSR))
	{
		if (mode == 1)
			ft_putstr_fd("You cannot execute the file (´ ͡༎ຶ ͜ʖ ͡༎ຶ )\n", 2);
		return (1);
	}
	else if (S_ISDIR(filestat.st_mode))
	{
		if (mode == 1)
			ft_putstr_fd("Hum, apparently it's a folder (●__●)\n", 2);
		return (1);
	}
	else if (mode == 1)
	{
		ft_putstr_fd("Unknown error, but it's not working\n", 2);
		return (1);
	}
	return (0);
}
