/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_edition.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymarcill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/16 15:03:03 by ymarcill          #+#    #+#             */
/*   Updated: 2019/09/18 17:24:32 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <input.h>

int		init(int *mainindex, int **prompt, t_coord *c)
{
	ft_bzero(&c, sizeof(c));
	*mainindex = 0;
	if (set_none_canon_mode(0) == -1)
	{
		free(g_mainline);
		return (-1);
	}
	if (g_mainline)
	{
		free(g_mainline);
		g_mainline = NULL;
	}
	g_mainline = ft_strnew(1);
	singleton(0);
	signal(SIGINT, signalhandler);
	prompt[0] = get_coord(get_cursor_position());
	return (0);
}

char	*read_quit(int **prompt, int **pos)
{
	struct s_coord	c;

	c.buf = ft_strnew(9);
	if ((c.ret = read(0, c.buf, 8)) <= 0 || (c.buf[0] == 4 && c.buf[1] == 0
		&& g_mainline[0] == 0))
	{
		ft_putstr_fd("exit", 0);
		reset_shell_attr(0);
		free(prompt[0]);
		free(c.buf);
		free(pos[0]);
		free(g_mainline);
		return (NULL);
	}
	c.buf[c.ret] = '\0';
	return (c.buf);
}

int		control_c(char *buf, int *prompt, int *coord, int r)
{
	struct s_coord	c;

	if (buf[0] == 7 && !buf[1])
	{
		r = r + get_nb_line_quote(g_mainline);
		c.t = r;
		if (coord[0] >= prompt[0] &&
				coord[0] < prompt[0] + r)
			c.t = coord[0] - prompt[0];
		while (c.t++ < r)
			ft_putstr_fd("\e[B", 0);
		ft_putstr_fd("\n\r", 0);
		free(g_mainline);
		g_mainline = NULL;
		return (0);
	}
	return (-1);
}

int		main_core(char *buf, int **prompt, int **pos, int *mainindex)
{
	int	r;

	if (buf[0] != '\n' && buf[0] > 31 && buf[0] < 127)
		print_char(mainindex, buf, prompt, pos);
	r = get_row(0, ft_strlenu(g_mainline), prompt[0][1]);
	move_with_arrows(buf, prompt[0], mainindex, pos[0]);
	move_toword(buf, prompt[0], mainindex, pos[0]);
	ft_copy_paste(buf, prompt, mainindex, pos);
	return (r);
}

int		entry(int r, t_hustru *big_struc, int *coord, int *prompt)
{
	struct s_coord	c;

	r = r + get_nb_line_quote(g_mainline);
	c.t = r;
	if (coord[0] >= prompt[0] && coord[0] < prompt[0] + r)
		c.t = coord[0] - prompt[0];
	while (c.t++ < r)
		ft_putstr_fd("\e[B", 0);
	ft_putstr_fd("\n\r", 0);
	g_mainline = get_quotes(g_mainline, big_struc);
	if (g_mainline[0])
		save_command(big_struc, g_mainline, 1);
	free(coord);
	free(prompt);
	return (1);
}

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
		//free(c.pos);
		c.pos = move_hist(c.buf, &c.prompt, big_struc, &c.mainindex);
		if (c.buf[0] == '\n' && entry(c.r, big_struc, c.coord, c.prompt))
		{
			free(c.buf);
			printf("g_mainline = %s\n", g_mainline);
			//free(c.pos);
			return (0);
		}
		free(c.coord);
		free(c.buf);
	}
		return (0);
}
