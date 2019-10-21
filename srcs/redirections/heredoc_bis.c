/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_bis.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymarcill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/21 15:01:58 by ymarcill          #+#    #+#             */
/*   Updated: 2019/10/21 18:50:27 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <input.h>

int		do_heredoc(t_hustru *big_struc, char **command)
{
	int link[2];

	if (pipe(link) == -1)
		return (0);
	ft_putstr_fd(heredoc(big_struc, command), link[1]);
	close(link[1]);
	dup2(link[0], 0);
	return (0);
}

void	free_fornorme(int i, t_coord *c, char **arg_tab)
{
	char	*tmp2;

	if (i == 0)
	{
		free(c->buf);
		free(c->coord);
	}
	else if (i == 1)
	{
		if (arg_tab[1])
			tmp2 = ft_strdup(g_mainline);
		else
			tmp2 = ft_strjoin(c->tmp, g_mainline);
		free(c->tmp);
		c->tmp = ft_strjoin(tmp2, "\n");
		free(tmp2);
	}
}
