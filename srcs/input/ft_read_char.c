/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_char.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymarcill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/24 20:22:12 by ymarcill          #+#    #+#             */
/*   Updated: 2019/09/24 21:28:54 by ymarcill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <input.h>

int		ft_read_1(t_hustru *big_struc)
{
	t_coord c;

	if (init(&c.mainindex, &c.prompt, &c) == -1)
		return (-1);
	while (42)
	{
		if ((c.buf = read_quit(&c.prompt, &c.pos)) == NULL)
			return (-1);
		c.coord = get_coord(get_cursor_position());
		if (control_c(c.buf, c.prompt, c.coord, c.r) == 0)
			return (0);
		c.prompt[0] = c.coord[0] == 1 ? 1 : c.prompt[0];
		c.r = main_core(c.buf, &c.prompt, &c.pos, &c.mainindex);
		free(c.pos);
		c.pos = move_hist(c.buf, &c.prompt, big_struc, &c.mainindex);
		if (c.buf[0] == '\n' && entry(c.r, big_struc, c.coord, c.prompt))
		{
			free(c.buf);
			free(c.pos);
			return (0);
		}
		free(c.coord);
		free(c.buf);
	}
	return (0);
}
