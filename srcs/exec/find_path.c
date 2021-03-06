/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/15 16:46:50 by lubenard          #+#    #+#             */
/*   Updated: 2019/10/25 12:33:56 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh21.h>

int		is_valid_command(t_hustru *big_struc, char **argv)
{
	char	*path;

	path = NULL;
	if (ft_strcmp(argv[0], "env")
	&& ft_strcmp(argv[0], "setenv")
	&& ft_strcmp(argv[0], "unsetenv")
	&& ft_strcmp(argv[0], "echo")
	&& ft_strcmp(argv[0], "cd")
	&& ft_strcmp(argv[0], "history")
	&& ft_strcmp(argv[0], "exit")
	&& !(path = find_path(big_struc->path, argv[0])))
	{
		free(path);
		return (invalid_command(argv[0]));
	}
	free(path);
	return (0);
}

char	*search_absolute_path2(char *command, char *str, char *str2)
{
	free(str);
	free(str2);
	return (ft_strdup(command));
}

/*
** Used to find absolute path
*/

char	*search_absolute_path(char *command)
{
	char	*str;
	char	*str2;
	char	buff[6000];

	if (!command)
		return (NULL);
	str2 = ft_strjoin(getcwd(buff, 6000), "/");
	str = ft_strjoin(str2, command);
	if (command[0] != '/' && ft_strncmp(command, "..", 2)
	&& command[0] && !access(str, F_OK))
	{
		ft_strdel(&str2);
		if (ft_strchr(command, '/'))
			return (str);
		ft_strdel(&str);
		return (NULL);
	}
	else if (access(command, F_OK) != -1)
		return (search_absolute_path2(command, str, str2));
	ft_strdel(&str);
	ft_strdel(&str2);
	return (NULL);
}

/*
** Used to find path in $PATH or absolute path
*/

char	*find_path(char **path, char *first_command)
{
	int				i;
	struct dirent	*p_dirent;
	DIR				*p_dir;
	char			*does_it_exist;
	int				e;

	i = 0;
	while ((e = (path != NULL) ? 1 : 0) == 1 && path[i])
	{
		if ((p_dir = opendir(path[i])))
		{
			while ((p_dirent = readdir(p_dir)) != NULL)
			{
				if (ft_strcmp(p_dirent->d_name, first_command) == 0)
				{
					closedir(p_dir);
					return (ft_strjoin(path[i], first_command));
				}
			}
			closedir(p_dir);
		}
		i++;
	}
	return (does_it_exist = search_absolute_path(first_command));
}
