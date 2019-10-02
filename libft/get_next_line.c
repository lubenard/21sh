/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <lubenard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/25 11:00:13 by lubenard          #+#    #+#             */
/*   Updated: 2019/10/02 17:16:47 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char			*read_line(char **gnl, char *buf, int fd)
{
	char		*tmp;
	int			ret;

	ret = 1;
	while (!ft_strchr(*gnl, '\n') && ret)
	{
		ret = read(fd, buf, BUFF_SIZE);
		if (ret)
		{
			buf[ret] = '\0';
			tmp = *gnl;
			if (!(*gnl = ft_strjoin(tmp, buf)))
				return (NULL);
			free(tmp);
		}
	}
	free(buf);
	return (*gnl);
}

char			*save_line(char **gnl)
{
	char		*buf;
	char		*newline;
	char		*tmp;

	buf = ft_strchr(*gnl, '\n');
	tmp = NULL;
	if (buf)
	{
		if (!(newline = ft_strndup(*gnl, buf - *gnl)))
			return (NULL);
		tmp = *gnl;
		if (!(*gnl = ft_strdup(buf + 1)))
			return (NULL);
		free(tmp);
	}
	else if (!(newline = ft_strdup(*gnl)))
		return (NULL);
	if (!(*gnl) || !tmp)
	{
		free(*gnl);
		*gnl = NULL;
	}
	return (newline);
}

int				get_next_line(const int fd, char **line)
{
	static char	*gnl = NULL;
	char		*buf;

	if (fd < 0 || !line || BUFF_SIZE <= 0 || !(buf = ft_strnew(BUFF_SIZE + 1)) \
		|| read(fd, buf, 0) == -1 || (gnl == NULL && !(gnl = ft_strnew(0))))
		return (-1);
	if (!(read_line(&gnl, buf, fd)))
		return (-1);
	if (*gnl)
	{
		if (!(*line = save_line(&gnl)))
			return (-1);
		return (1);
	}
	return (0);
}
