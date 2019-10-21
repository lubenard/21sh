/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/21 17:44:31 by lubenard          #+#    #+#             */
/*   Updated: 2019/10/21 17:45:40 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh21.h>

/*
** Handle pipe and heredoc
*/

char	*pipe_heredoc(t_hustru *big_struc, char ***command)
{
	int		i;
	char	*str;

	i = 0;
	str = NULL;
	while (command[i])
	{
		if (ft_tabstr(command[i], "<<"))
		{
			remove_quote(&command[i]);
			big_struc->pipe_heredoc = heredoc(big_struc, command[i]);
		}
		i++;
	}
	return (str);
}

void	do_heredoc_pipe(t_hustru *big_struc, char ***tab, int j)
{
	int link[2];

	if (big_struc->pipe_heredoc && ft_tabstr(tab[j], "<<"))
	{
		if (pipe(link) == -1)
			;
		ft_putstr_fd(big_struc->pipe_heredoc, link[1]);
		close(link[1]);
		dup2(link[0], 0);
	}
}
