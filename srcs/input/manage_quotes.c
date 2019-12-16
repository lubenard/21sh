/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymarcill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/20 17:08:51 by ymarcill          #+#    #+#             */
/*   Updated: 2019/11/19 01:21:45 by ymarcill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <input.h>

char	*read_quit_q(int **prompt, int **pos)
{
	t_coord c;

	c.buf = ft_strnew(9);
	if ((c.ret = read(0, c.buf, 8)) <= 0)
	{
		ft_putstr_fd("exit\n", 2);
		reset_shell_attr(0);
		free(prompt[0]);
		free(*pos);
		free(c.buf);
		free(g_mainline);
		return (NULL);
	}
	c.buf[c.ret] = '\0';
	return (c.buf);
}

char	*entry_q(int r, int *coord, int *prompt, char *line)
{
	int		t;
	char	*tmp;

	t = r;
	if (coord[0] >= prompt[0] & coord[0] < prompt[0] + r)
		t = coord[0] - prompt[0];
	while (t++ < r)
		ft_putstr_fd("\e[B", 0);
	ft_putstr_fd("\r", 0);
	tmp = ft_strdup(g_mainline);
	free(g_mainline);
	g_mainline = ft_strjoin(tmp, "\n");
	free(tmp);
	tmp = ft_strdup(line);
	free(line);
	line = ft_strjoin(tmp, g_mainline);
	free(tmp);
	free(prompt);
	ft_strdel(&g_mainline);
	return (line);
}

void	initi(int *mainindex, int **prompt, char **buf)
{
	(void)buf;
	*mainindex = 0;
	ft_strdel(&g_mainline);
	g_mainline = ft_strnew(1);
	prompt[0] = get_coord(get_cursor_position());
	signal(SIGINT, signalhandler);
}

char	*get_inline(char *line, t_hustru *big_struc)
{
	t_coord		c;

	initi(&c.mainindex, &c.prompt, &c.buf);
	c.pos = NULL;
	while (42)
	{
		if ((c.buf = read_quit_q(&c.prompt, &c.pos)) == NULL)
			return (line);
		c.coord = get_coord(get_cursor_position());
		c.prompt[0] = c.coord[0] == 1 ? 1 : c.prompt[0];
		c.r = main_core(c.buf, &c.prompt, &c.pos, &c.mainindex);
		move_hist(&c, big_struc);
		if ((c.buf[0] == '\n' &&
					(line = entry_q(c.r, c.coord, c.prompt, line)))
				|| control_c(c.buf, c.prompt, c.coord, c.r) == 0)
		{
			c.buf[0] == '\n' ? free(c.coord) : 0;
			line = (c.buf[0] == '\n') ? line : ft_strjoinfree(line, c.buf);
			free(c.buf);
			free(c.pos);
			return (line);
		}
		free(c.coord);
		free(c.buf);
	}
}

char	*get_quotes(char *line, t_hustru *big_struc)
{
	int		i;
	char	*tmp;

	i = 0;
	tmp = NULL;
	line = ft_strjoinnf(line, "\n");
	while (line && line[i])
	{
		if (line && (line[i] == '\'' || line[i] == '\"'))
			line = do_i_have_to_do_it_quote(line, &i, big_struc, &tmp);
		if (line && line[ft_strlenu(line) - 1] == 7)
		{
			line[ft_strlenu(line) - 1] = '\0';
			ft_strdel(&line);
			break ;
		}
		i++;
	}
	if (tmp && tmp[0] == 'y' && line[ft_strlenu(line) - 1] != '\''
			&& line[ft_strlenu(line) - 1] != '\"')
		line = suppr_lastchar(line);
	return (line);
}
