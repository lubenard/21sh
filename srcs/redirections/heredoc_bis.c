/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_bis.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymarcill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/21 15:01:58 by ymarcill          #+#    #+#             */
/*   Updated: 2019/10/21 15:03:01 by ymarcill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <input.h>

void    free_fornorme(int i, t_coord *c, char **arg_tab)
{
	char    *tmp2;

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

