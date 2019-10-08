/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymarcill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/18 10:59:34 by ymarcill          #+#    #+#             */
/*   Updated: 2019/10/08 15:51:05 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <input.h>

char	**fill_arg_tab(char **tab_line, char **arg_tab, int *j)
{
	int	i;
	int	a;

	i = 0;
	a = 0;
	while (tab_line[i])
	{
		if (ft_strcmp(tab_line[i], "<<") == 0)
			a += 1;
		i++;
	}
	arg_tab = malloc(sizeof(char*) * (a + 2));
	i = 0;
	a = 0;
	while (tab_line[i])
	{
		if (ft_strcmp(tab_line[i], "<<") == 0)
			arg_tab[a++] = ft_strdup(tab_line[i + 1]);
		i++;
	}
	arg_tab[a] = NULL;
	*j = a;
	return (arg_tab);
}

int			entry_h(t_coord *c, char **arg_tab)
{
	char	*tmp2;
	
	tmp2 = ft_strjoin(c->tmp, g_mainline);
	free(c->tmp);
	c->tmp = ft_strjoin(tmp2, "\n");
	free(tmp2);
	c->mainindex = 0;
	ft_putstr_fd("\n", 0);
	if (ft_strcmp(g_mainline, arg_tab[c->i]) == 0)
	{
		c->r = c->r + get_nb_line_quote(g_mainline);
		c->t = c->r;
		if (c->coord[0] >= c->prompt[0] && c->coord[0] < c->prompt[0] + c->r)
			c->t = c->coord[0] - c->prompt[0];
		while (c->t++ < c->r)
			ft_putstr_fd("\e[B", 0);
		c->i++;
	}
	free(g_mainline);
	if (c->i == c->j)
	{
		free(c->pos);
		return (0);
	}
	else
		ft_putstr_fd("heredoc> ", 2);
	return (-1);
}

int		init_h(t_coord *c, char ***arg_tab, char **tab_line)
{
	ft_bzero(c, sizeof(c));
	c->tmp = ft_strnew(1);
	free(g_mainline);
	g_mainline = ft_strnew(1);
	c->i = 0;
	*arg_tab = fill_arg_tab(tab_line, *arg_tab, &c->j);
	if (init(&c->mainindex, &c->prompt, c) == -1)
		return (-1);
	ft_putstr_fd("heredoc> ", 2);
	return (0);
}

char	*heredoc(t_hustru *big_struc, char **tab_line)
{
	t_coord	c;
	char	**arg_tab;

	tab_line = malloc(sizeof(char*) * 9);
	tab_line[0] = ft_strdup("coucou");
	tab_line[1] = ft_strdup("<<");
	tab_line[2] = ft_strdup("1");
	tab_line[3] = ft_strdup("<<");

	tab_line[4] = ft_strdup("2");
	tab_line[5] = ft_strdup("<<");
	tab_line[6] = ft_strdup("3");
	tab_line[7] = NULL;
	if (init_h(&c, &arg_tab, tab_line) == -1 || tab_line == NULL)
		return (c.tmp);
	c.pos = NULL;
	while (42)
	{
		if ((c.buf = read_quit(&c.prompt, &c.pos)) == NULL)
			return (c.tmp);
		c.coord = get_coord(get_cursor_position());
		if (control_c(c.buf, c.prompt, c.coord, c.r) == 0)
			return (c.tmp);
		c.prompt[0] = c.coord[0] == 1 ? 1 : c.prompt[0];
		c.r = main_core(c.buf, &c.prompt, &c.pos, &c.mainindex);
		move_hist(&c, big_struc);
		if (c.buf[0] == '\n') //&& ft_strcmp(g_mainline, arg_tab[c.i]) == 0)
		{
			if (entry_h(&c, arg_tab) == 0)
				return (c.tmp);
			g_mainline = ft_strnew(1);
		}
		free(c.buf);
		free(c.coord);
	}
}
