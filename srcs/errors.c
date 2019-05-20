/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/03 17:01:28 by lubenard          #+#    #+#             */
/*   Updated: 2019/05/20 18:36:20 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

void	error(char *command)
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

int		free_after_exec(char *get_right_path, char **argv,
	char **env)
{
	int i;

	i = 0;
	while (argv[i])
		free(argv[i++]);
	free(get_right_path);
	//free(argv);
	free(env);
	return (0);
}

char	*extract_command(char *command)
{
	int i;
	int e;

	i = 0;
	e = 0;
	while (command[e] == ' ' || command[e] == '\t')
		e++;
	while (ft_isalnum(command[i + e])
	|| command[i + e] == '.' || command[i + e] == '/')
		++i;
	return (ft_strlower(ft_strsub(command, e, i)));
}
