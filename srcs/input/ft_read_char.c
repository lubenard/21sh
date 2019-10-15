/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_char.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymarcill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/24 20:22:12 by ymarcill          #+#    #+#             */
/*   Updated: 2019/10/15 21:12:24 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <input.h>

int		ft_read_1(t_hustru *big_struc)
{
	t_coord c;

	if (init(&c.mainindex, &c.prompt, &c) == -1)
		return (-1);
	c.pos = NULL;
	while (42)
	{
		if ((c.buf = read_quit(&c.prompt, &c.pos)) == NULL)
			return (-1);
		c.coord = get_coord(get_cursor_position());
		c.prompt[0] = c.coord[0] == 1 ? 1 : c.prompt[0];
		c.r = main_core(c.buf, &c.prompt, &c.pos, &c.mainindex);
		move_hist(&c, big_struc);
		if (control_c(c.buf, c.prompt, c.coord, c.r) == 0
		|| (c.buf[0] == '\n' && entry(c.r, big_struc, c.coord, c.prompt)))
		{
			free(c.pos);
			free(c.buf);
			return (0);
		}
		free(c.coord);
		free(c.buf);
	}
	return (0);
}
