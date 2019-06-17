/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cursor_pos.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymarcill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/21 20:16:02 by ymarcill          #+#    #+#             */
/*   Updated: 2019/06/17 14:43:54 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <input.h>

char	*get_cursor_position(void)
{
	char	buf[255];
	int		ret;
	char	*tmp;

	write(1, "\033[6n", 4);
	if ((ret = read(1, buf, 254)) == -1)
		return (NULL);
	buf[ret] = '\0';
	tmp = ft_strdup(buf);
	return (tmp);
}

/*
** Use ioctl to get the max size of the term
*/

int		alloc(t_coord *co)
{
	co->tmpx = ft_strnew(1023);
	if (!co->tmpx || !(co->tmpy = malloc(sizeof(char) * 1024)))
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
	return (0);
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
		{
			while (buf[co.i] && buf[++co.i] != ';')
				co.tmpx[co.j++] = buf[co.i];
			co.tmpx[co.j] = '\0';
		}
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
	return (co.coord);
}
