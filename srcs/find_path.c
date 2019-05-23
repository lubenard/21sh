/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/15 16:46:50 by lubenard          #+#    #+#             */
/*   Updated: 2019/05/24 00:11:05 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

char	*search_absolute_path2(char *command, char *str, char *str2)
{
	int length;

	length = ft_strlen(command);
	while (command[length] != '/')
		length--;
	free(str);
	free(str2);
	return (ft_strndup(command, length + 1));
}

char	*search_absolute_path(char *command)
{
	char	*str;
	char	*str2;
	char	buff[6000];

	str2 = ft_strjoin(getcwd(buff, 6000), "/");
	str = ft_strjoin(str2, command);
	if (command[0] != '/' && ft_strncmp(command, "..", 2)
	&& command[0] && !access(str, F_OK))
	{
		free(str);
		if (ft_strchr(command, '/'))
			return (str2);
		free(str2);
		return (NULL);
	}
	else if (access(command, F_OK) != -1)
		return (search_absolute_path2(command, str, str2));
	free(str);
	free(str2);
	return (NULL);
}

char	*find_path(char **path, char *first_command)
{
	int				i;
	struct dirent	*p_dirent;
	DIR				*p_dir;
	char			*does_it_exist;
	int				e;

	i = 0;
	e = (path != NULL) ? 1 : 0;
	while (e == 1 && path[i])
	{
		p_dir = opendir(path[i]);
		while ((p_dirent = readdir(p_dir)) != NULL)
		{
			if (ft_strcmp(p_dirent->d_name, first_command) == 0)
			{
				closedir(p_dir);
				return (ft_strdup(path[i]));
			}
		}
		closedir(p_dir);
		i++;
	}
	if ((does_it_exist = search_absolute_path(first_command)))
		return (does_it_exist);
	return (NULL);
}
