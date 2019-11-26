/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_char.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymarcill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/24 20:22:12 by ymarcill          #+#    #+#             */
/*   Updated: 2019/11/26 17:28:48 by ymarcill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <input.h>

void	free_fn(int *coord, char *buf)
{
	free(coord);
	free(buf);
}

int		ft_read_1(t_hustru *big_struc)
{
	t_coord c;

	if (init(&c.mainindex, &c.prompt, &c) == -1)
		return (-1);
	c.pos = NULL;
	while (42)
	{
		if ((c.buf = read_quit(&c.prompt, &c.pos, 'l')) == NULL)
			return (-1);
		c.coord = get_coord(get_cursor_position());
		if (isatty(0))
			c.prompt[0] = c.coord[0] == 1 ? 1 : c.prompt[0];
		if (isatty(0) == 0 || control_c(c.buf, c.prompt, c.coord, c.r) == 0
		|| (c.buf[0] == 10 && entry(c.r, big_struc, c.coord, c.prompt)))
		{
			isatty(0) ? free(c.pos) : 0;
			g_mainline = !isatty(0) ? c.buf : g_mainline;
			!isatty(0) ? 0 : ft_strdel(&c.buf);
			return (0);
		}
		c.r = main_core(c.buf, &c.prompt, &c.pos, &c.mainindex);
		move_hist(&c, big_struc);
		free_fn(c.coord, c.buf);
	}
	return (0);
}
