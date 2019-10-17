/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_error_lexer.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 13:41:01 by lubenard          #+#    #+#             */
/*   Updated: 2019/10/17 14:05:16 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <input.h>

int		is_elem_error(t_coord c, char **tab_q)
{
	c.c  = tab_q[c.i][c.j];
	c.k = tab_q[c.i][c.j + 1];
	c.x = c.k && tab_q[c.i][c.j + 2] ? tab_q[c.i][c.j+ 2] : 0;;
	if ((c.j > 0 && tab_q[c.i][c.j - 1] == '&') || (c.c == '<' && c.k &&
		(c.k == '&' || c.k == '>'|| (c.k == c.c && c.x))) || (c.c == '>' &&
		tab_q[c.i][c.j + 1] && ((tab_q[c.i][c.j + 1] == '&' && c.x)
		|| tab_q[c.i][c.j + 1] == '<' || (tab_q[c.i][c.j + 1] == c.c && c.x))))
	{
		ft_putstr("ymarsh: parse error near: \'");
		tab_q[c.i + 1] ? ft_putstr(tab_q[c.i + 1]) : ft_putstr(tab_q[c.i]);
		ft_putendl("\'");
		ft_deltab(tab_q);
		return (-1);
	}
	return (0);
}

int		is_next_elem_error(t_coord c, char **tab_q)
{
	if (ft_strcmp(tab_q[c.i], "<<") == 0 || ft_strcmp(tab_q[c.i], ">>") == 0
		|| ft_strcmp(tab_q[c.i], ">&") == 0 || ft_strcmp(tab_q[c.i], ">") == 0
		|| ft_strcmp(tab_q[c.i], "<") == 0)
	{
		if ((tab_q[c.i + 1] && (tab_q[c.i + 1][c.j] == '<'
			|| tab_q[c.i + 1][c.j] == '>')) ||  !tab_q[c.i + 1])
		{
			ft_putstr("ymarsh: parse error near: \'");
			tab_q[c.i + 1] ? ft_putstr(tab_q[c.i + 1]) : ft_putstr(tab_q[c.i]);
			ft_putendl("\'");
			ft_deltab(tab_q);
			return (-1);
		}
	}
	return (0);
}

int		is_semic_error(t_coord c, char **tab_q)
{
	if (c.i > 0 && tab_q[c.i - 1])
		c.k = tab_q[c.i - 1][0];
	if (tab_q[c.i][0] == ';' && (tab_q[c.i][1] == ';'
		|| (tab_q[c.i + 1] && tab_q[c.i + 1][0] == ';')
			|| !tab_q[c.i + 1] || (c.k && (c.k == '<' || c.k == '>' || c.k == '&'))))
	{
		ft_deltab(tab_q);
		ft_putendl("ymarsh: parse error near \';\'");
		return (-1);
	}
	return (0);
}

int		check_error_lexer(char **tab_q)
{
	t_coord	c;

	ft_bzero(&c, sizeof(c));
	while (tab_q && tab_q[c.i])
	{
		if (is_semic_error(c, tab_q) == -1)
			return (-1);
		while (tab_q[c.i][c.j])
		{
			if (tab_q[c.i][c.j] == '\"' || tab_q[c.i][c.j] == '\'')
				c.q_state = c.q_state == 0 ? 1 : 0;
			if (c.q_state == 0 && (tab_q[c.i][c.j] == '>' || tab_q[c.i][c.j] == '<'))
			{
				if (is_elem_error(c, tab_q) == -1)
					return (-1);
			}
			c.j++;
		}
		c.j = 0;
		if (is_next_elem_error(c, tab_q) == -1)
			return (-1);
		c.i++;
	}
	return (0);
}
