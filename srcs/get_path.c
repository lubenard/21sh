/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/14 22:01:21 by lubenard          #+#    #+#             */
/*   Updated: 2019/06/11 08:46:55 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh21.h>

int		ft_len(char *path_line)
{
	int i;
	int j;

	i = 4;
	j = 0;
	while (path_line[i] != '\0')
	{
		if (path_line[i] == ':')
			++j;
		++i;
	}
	return (++j);
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
	free(path_line);
	path[k] = NULL;
	return (path);
}
