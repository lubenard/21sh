/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymarcill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/20 17:08:51 by ymarcill          #+#    #+#             */
/*   Updated: 2019/09/24 20:29:16 by ymarcill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <input.h>

char	*entry_q(int r, int *coord, int *prompt, char *line)
{
	int t;

	t = r;
	if (coord[0] >= prompt[0] & coord[0] < prompt[0] + r)
		t = coord[0] - prompt[0];
	while (t++ < r)
		ft_putstr_fd("\e[B", 0);
	ft_putstr_fd("\r", 0);
	g_mainline = ft_strjoinnf(g_mainline, "\n");
	line = ft_strjoinnf(line, g_mainline);
	return (line);
}

void	initi(int *mainindex, int **prompt, char **buf)
{
	*mainindex = 0;
	free(g_mainline);
	g_mainline = ft_strnew(1);
	prompt[0] = get_coord(get_cursor_position());
	*buf = malloc(sizeof(char) * 9);
}

char	*get_inline(char *line, t_hustru *big_struc)
{
	t_coord		c;
	int			mainindex;

	initi(&mainindex, &c.prompt, &c.buf);
	while (42)
	{
		bzero(c.buf, sizeof(9));
		if ((c.ret = read(0, c.buf, 8)) == -1)
			return (line);
		c.buf[c.ret] = '\0';
		c.coord = get_coord(get_cursor_position());
		if (c.buf[0] == 7 && !c.buf[1])
		{
			line = ft_strjoinnf(line, c.buf);
			return (line);
		}
		if (c.coord[0] == 1)
			c.prompt[0] = 1;
		c.r = main_core(c.buf, &c.prompt, &c.pos, &mainindex);
		free(c.pos);
		c.pos = move_hist(c.buf, &c.prompt, big_struc, &mainindex);
		if (c.buf[0] == '\n' && (line = entry_q(c.r, c.coord, c.prompt, line)))
			return (line);
		free(c.coord);
	}
}

char	*get_quotes(char *line, t_hustru *big_struc)
{
	int		i;
	char	*tmp;

	i = 0;
	tmp = NULL;
	while (line[i])
	{
		if (line[i] == '\'' || line[i] == '\"')
			line = do_i_have_to_do_it_quote(line, &i, big_struc, &tmp);
		if (line[ft_strlenu(line) - 1] == 7)
		{
			line[ft_strlenu(line) - 1] = '\0';
			break ;
		}
		i++;
	}
	if (tmp && tmp[0] == 'y')
		line = suppr_lastchar(line);
	return (line);
}
