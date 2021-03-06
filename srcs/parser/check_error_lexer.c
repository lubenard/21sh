/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_error_lexer.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymarcill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/21 15:00:02 by ymarcill          #+#    #+#             */
/*   Updated: 2019/10/21 15:22:11 by ymarcill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <input.h>

int	is_elem_error(t_coord c, char **tab_q)
{
	c.c = tab_q[c.i][c.j];
	c.k = tab_q[c.i][c.j + 1];
	c.x = c.k && tab_q[c.i][c.j + 2] ? tab_q[c.i][c.j + 2] : 0;
	if ((c.j > 0 && tab_q[c.i][c.j - 1] == '&') || (c.c == '<' && c.k &&
		(c.k == '&' || c.k == '>' || (c.k == c.c && c.x))) || (c.c == '>' &&
		tab_q[c.i][c.j + 1] && ((c.k == '&' && (!ft_isdigit(c.x) && c.x != '-'))
		|| tab_q[c.i][c.j + 1] == '<' || (tab_q[c.i][c.j + 1] == c.c && c.x))))
	{
		ft_putstr_fd("Ymarsh: parse error near: \'", 2);
		tab_q[c.i + 1] ? ft_putstr_fd(tab_q[c.i + 1], 2)
						: ft_putstr_fd(tab_q[c.i], 2);
		ft_putendl_fd("\'", 2);
		return (-1);
	}
	return (0);
}

int	is_next_elem_error(t_coord c, char **tab_q)
{
	if (ft_strcmp(tab_q[c.i], "<<") == 0 || ft_strcmp(tab_q[c.i], ">>") == 0
		|| ft_strcmp(tab_q[c.i], ">&") == 0 || ft_strcmp(tab_q[c.i], ">") == 0
		|| ft_strcmp(tab_q[c.i], "<") == 0)
	{
		if ((tab_q[c.i + 1] && (tab_q[c.i + 1][c.j] == '<'
			|| tab_q[c.i + 1][c.j] == '>')) || !tab_q[c.i + 1])
		{
			ft_putstr_fd("ymarsh: parse error near: \'", 2);
			tab_q[c.i + 1] ? ft_putstr_fd(tab_q[c.i + 1], 2) :
							ft_putstr_fd(tab_q[c.i], 2);
			ft_putendl_fd("\'", 2);
			return (-1);
		}
	}
	return (0);
}

int	is_file_error(t_coord c, char **tab_q)
{
	if (ft_strcmp(tab_q[c.i], "<") == 0 && tab_q[c.i + 1]
		&& access(tab_q[c.i + 1], F_OK) == -1)
	{
		ft_putstr_fd("ymarsh: no such file or directory: ", 2);
		ft_putendl_fd(tab_q[c.i + 1], 2);
		return (-1);
	}
	return (0);
}

int	check_error_lexer(char **tab_q)
{
	t_coord	c;

	ft_bzero(&c, sizeof(c));
	while (tab_q && tab_q[c.i])
	{
		if (is_file_error(c, tab_q) == -1)
			return (-1);
		while (tab_q[c.i][c.j])
		{
			if (tab_q[c.i][c.j] == '\"' || tab_q[c.i][c.j] == '\'')
				c.q_stat = c.q_stat == 0 ? 1 : 0;
			if (c.q_stat == 0 && (tab_q[c.i][c.j] == '>' ||
				tab_q[c.i][c.j] == '<'))
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
