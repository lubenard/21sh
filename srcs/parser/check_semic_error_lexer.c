/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_semic_error_lexer.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymarcill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/21 14:59:45 by ymarcill          #+#    #+#             */
/*   Updated: 2019/10/21 15:09:57 by ymarcill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <input.h>

int		is_semic_error(t_coord c, char **tab_q)
{
	if (c.i > 0 && tab_q[c.i - 1])
		c.k = tab_q[c.i - 1][0];
	if (tab_q[c.i][0] == ';' && (tab_q[c.i][1] == ';'
		|| (tab_q[c.i + 1] && tab_q[c.i + 1][0] == ';')
		|| !tab_q[c.i + 1] || (c.k && (c.k == '<' || c.k == '>'
													|| c.k == '&'))))
	{
		ft_deltab(tab_q);
		ft_putendl_fd("ymarsh: parse error near \';\'", 2);
		return (-1);
	}
	return (0);
}

int		check_semic_error(char **tab_q)
{
	t_coord	c;

	ft_bzero(&c, sizeof(c));
	while (tab_q && tab_q[c.i])
	{
		if (is_semic_error(c, tab_q) == -1)
			return (-1);
		c.i++;
	}
	return (0);
}
