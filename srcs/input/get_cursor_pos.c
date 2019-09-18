/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cursor_pos.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymarcill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/21 20:16:02 by ymarcill          #+#    #+#             */
/*   Updated: 2019/09/17 19:48:22 by ymarcill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <input.h>

char	*get_cursor_position(void)
{
	char	buf[255];
	int		ret;
	char	*tmp;

	write(1, "\033[6n", 4);
	tmp = ft_strnew(1);
	if ((ret = read(0, buf, 254)) == -1)
		return (tmp);
	buf[ret] = '\0';
	free(tmp);
	tmp = ft_strdup(buf);
	return (tmp);
}

int		alloc(t_coord *co)
{
	if (!(co->tmpx = malloc(sizeof(char) * 1024))
		|| !(co->tmpy = malloc(sizeof(char) * 1024)))
	{
		if (co->tmpx)
			free(co->tmpx);
		return (-1);
	}
	if (!(co->coord = malloc(sizeof(int) * 2)))
	{
		free(co->tmpx);
		free(co->tmpy);
		return (-1);
	}
	ft_bzero(co->coord, sizeof(int) * 2);
	ft_bzero(co->tmpx, sizeof(char) * 1024);
	ft_bzero(co->tmpy, sizeof(char) * 1024);
	return (0);
}

char	*fill_screensz(char *buf, int *i, int *j, char *tmp)
{
	while (buf[*i] && buf[*i] != ';')
	{
		tmp[*j] = buf[*i];
		*j += 1;
		*i += 1;
	}
	tmp[*j] = '\0';
	return (tmp);
}

int		*get_coord(char *buf)
{
	t_coord co;

	ft_memset(&co, 0, sizeof(t_coord));
	if (alloc(&co) == -1 || !buf)
		return (NULL);
	while (buf[co.i++])
	{
		if (buf[co.i] == 91)
			co.tmpx = fill_screensz(buf, &co.i, &co.j, co.tmpx);
		if (buf[co.i] == ';')
		{
			while (buf[co.i] && buf[++co.i] != 'R')
				co.tmpy[co.k++] = buf[co.i];
			co.tmpy[co.k] = '\0';
		}
		co.coord[0] = ft_atoi(co.tmpx);
		co.coord[1] = ft_atoi(co.tmpy);
	}
	free(buf);
	free(co.tmpx);
	free(co.tmpy);
	return (co.coord);
}
