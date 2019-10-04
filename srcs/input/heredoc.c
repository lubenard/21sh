/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymarcill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/18 10:59:34 by ymarcill          #+#    #+#             */
/*   Updated: 2019/10/01 16:58:14 by ymarcill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <input.h>

char	*heredoc(char **tab_line, t_hustru *big_struc)
{
	t_coord		c;
	int			mainindex;
	char		*tmp;

	tmp = ft_strnew(1);
	c.line = ft_strnew(1);
	c.prompt = get_coord(get_cursor_position());
	while (ft_strcmp(tab_line[c.i], "<<"))
		c.i++;
	while (42)
	{
		if ((c.buf = read_quit()) == NULL)
			return (tmp);
		c.coord = get_coord(get_cursor_position());
		if (control_c(c.buf, c.prompt, c.coord, c.r) == 0)
			return (tmp);
		c.prompt[0] = c.coord[0] == 1 ? 1 : c.prompt[0];
		c.r = main_core(c.buf, &c.prompt, &c.pos, &mainindex);
		move_hist(&c, big_struc);
		if (c.buf[0] == '\n' && ft_strcmp(g_mainline, tab_line[c.i + 1]))
		{
			c.r = c.r + get_nb_line_quote(g_mainline);
			c.t = c.r;
			if (c.coord[0] >= c.prompt[0] && c.coord[0] < c.prompt[0] + c.r)
				c.t = c.coord[0] - c.prompt[0];
			while (c.t++ < c.r)
				ft_putstr_fd("\e[B", 0);
			ft_putstr_fd("\n\r", 0);
			//return (0);
		}
		else if (c.buf[0] == '\n')
		{
			ft_putstr_fd("\n\r", 0);
			tmp = ft_strjoinnf(tmp, g_mainline);
			tmp = ft_strjoinnf(tmp, "\n");
			free(g_mainline);
			g_mainline = ft_strnew(1);
		}
		free(c.coord);
	}
}
