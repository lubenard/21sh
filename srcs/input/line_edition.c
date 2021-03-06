/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_edition.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymarcill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/16 15:03:03 by ymarcill          #+#    #+#             */
/*   Updated: 2020/01/07 10:53:49 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <input.h>

int		init(int *mainindex, int **prompt, t_coord *c)
{
	*mainindex = 0;
	if (set_none_canon_mode(0) == -1)
	{
		ft_strdel(&g_mainline);
		return (-1);
	}
	singleton(0);
	ft_bzero(&c, sizeof(c));
	ft_strdel(&g_mainline);
	g_mainline = ft_strnew(1);
	signal(SIGINT, signalhandler);
	if ((*prompt = get_coord(get_cursor_position())) == NULL)
	{
		ft_strdel(&g_mainline);
		return (-2);
	}
	return (0);
}

char	*read_quit(int **prompt, int **pos, char d)
{
	t_coord c;

	c.buf = ft_strnew(4096);
	if ((c.ret = read(0, c.buf, 4096)) <= 0 || (c.buf[0] == 4 && c.buf[1] == 0
		&& g_mainline[0] == 0))
	{
		if (d != 'h')
			ft_putstr_fd("exit\n", 2);
		reset_shell_attr(0);
		free(prompt[0]);
		free(*pos);
		free(c.buf);
		ft_strdel(&g_mainline);
		return (NULL);
	}
	c.buf[c.ret] = '\0';
	if ((c.x = none_asci(c.buf, 1)) <= 0 && isatty(0) == 0)
	{
		ft_strdel(&c.buf);
		ft_strdel(&g_mainline);
		free(prompt[0]);
		ft_putendl_fd("Sorry we do not support unicode, we must quit, bye", 2);
		return (NULL);
	}
	return (c.buf);
}

int		control_c(char *buf, int *prompt, int *coord, int r)
{
	struct s_coord	c;
	int				rr;

	rr = get_row(0, ft_strlenu(g_mainline), prompt[1]);
	if ((buf[0] == 7 && !r) || (buf[0] == 7 && !buf[1] && r))
	{
		rr = rr + get_nb_line_quote(g_mainline);
		c.t = rr;
		if (coord[0] >= prompt[0] &&
				coord[0] < prompt[0] + rr)
			c.t = coord[0] - prompt[0];
		while (c.t++ < rr)
			ft_putstr_fd("\e[B", 0);
		ft_putstr_fd("\n\r", 0);
		free(g_mainline);
		free(prompt);
		free(coord);
		g_mainline = NULL;
		return (0);
	}
	return (-1);
}

int		main_core(char *buf, int **prompt, int **pos, int *mainindex)
{
	int r;

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
	t_coord c;

	r = get_row(0, ft_first_occ(g_mainline, '\n'), prompt[1]);
	r += get_nb_line_quote(g_mainline);
	c.t = r;
	if (coord[0] >= prompt[0] && coord[0] < prompt[0] + r)
		c.t = coord[0] - prompt[0];
	while (c.t++ < r)
		ft_putstr_fd("\e[B", 0);
	ft_putstr_fd("\n\r", 0);
	while (big_struc->lkd_hist->next)
		big_struc->lkd_hist = big_struc->lkd_hist->next;
	g_mainline = get_quotes(g_mainline, big_struc);
	if (g_mainline && g_mainline[0] && ft_strisascii(g_mainline))
		save_command(big_struc, g_mainline, 1);
	free(coord);
	free(prompt);
	return (1);
}
