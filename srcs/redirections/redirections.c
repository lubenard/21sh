/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/16 17:57:01 by lubenard          #+#    #+#             */
/*   Updated: 2019/10/01 16:22:28 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh21.h>

void	redir_and_pipe(t_hustru *big_struc, char **command)
{
	(void)big_struc;
	(void)command;
}

int		redirections(t_hustru *big_struc, char *command)
{
	char **parsed_command;
	int i = 0; //used for debug online

	//parsed_command = parse_redir(command);
	parsed_command = ft_strsplit(command, ' ');
	while (parsed_command[i])
		printf("[Parsed redir] %s\n", parsed_command[i++]);
	//if (ft_strstr(command, "<<"))
	//	heredoc(big_struc, command);
	//else
	launch_arrow(big_struc, parsed_command);
	return (0);
}
