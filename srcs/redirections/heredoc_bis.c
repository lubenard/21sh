/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_bis.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymarcill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/21 15:01:58 by ymarcill          #+#    #+#             */
/*   Updated: 2020/01/07 12:32:32 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <input.h>

int		do_heredoc(t_hustru *big_struc, char **command)
{
	int		link[2];
	char	*tmp;

	if (pipe(link) == -1)
		return (0);
	tmp = heredoc(big_struc, command);
	ft_putstr_fd(tmp, link[1]);
	ft_strdel(&tmp);
	close(link[1]);
	dup2(link[0], 0);
	return (0);
}

void	free_fornorme(int i, t_coord *c, char **arg_tab)
{
	char		*tmp2;
	static int	check = 0;

	(void)arg_tab;
	if (i == 0)
	{
		free(c->buf);
		free(c->coord);
	}
	else if (i == 1)
	{
		if (c->i > check)
		{
			tmp2 = ft_strdup(g_mainline);
			check = c->i;
		}
		else
			tmp2 = ft_strjoin(c->tmp, g_mainline);
		free(c->tmp);
		c->tmp = ft_strjoin(tmp2, "\n");
		free(tmp2);
	}
}
