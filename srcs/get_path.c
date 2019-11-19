/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/14 22:01:21 by lubenard          #+#    #+#             */
/*   Updated: 2019/11/19 05:31:57 by ymarcill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh21.h>

/*
** This file transform $PATH var into double array
*/

int		ft_len(char *path_line)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (path_line && path_line[i] != '\0')
	{
		if (path_line[i] == ':')
			++j;
		++i;
	}
	return (++j);
}

char	**return_path(char **path, int k, char *path_line)
{
	free(path_line);
	path[k] = NULL;
	return (path);
}

char	**get_path(char *path_line)
{
	int		i;
	int		j;
	char	**path;
	int		k;
	char	*tmp;

	i = 0;
	j = 0;
	k = 0;
	if (!path_line
	|| !(path = (char **)malloc(sizeof(char *) * (ft_len(path_line) + 1))))
		return (NULL);
	while (k < ft_len(path_line))
	{
		while (path_line[i + j] && path_line[j + i] != ':')
			++i;
		tmp = ft_strsub(path_line, j, i);
		path[k] = ft_strjoin(tmp, "/");
		free(tmp);
		j += i + 1;
		i = 0;
		++k;
	}
	return (return_path(path, k, path_line));
}
