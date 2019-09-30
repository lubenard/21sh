/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/16 17:57:01 by lubenard          #+#    #+#             */
/*   Updated: 2019/09/30 17:36:11 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh21.h>

/*
** NOTES : arrow is creating the files before executing command
*/

void	redir_and_pipe(t_hustru *big_struc, char **command)
{
	(void)big_struc;
	(void)command;
}

void	double_redir(t_hustru *big_struc, char *command)
{
	(void)big_struc;
	(void)command;
}

int		redirections(t_hustru *big_struc, char *command)
{
	(void)big_struc;
	(void)command;
	char **parsed_command;
	int i = 0; //used for debug online

	//parsed_command = parse_redir(command);
	parsed_command = ft_strsplit(command, ' ');
	while (parsed_command[i])
		printf("[Parsed redir] %s\n", parsed_command[i++]);
	/*if (ft_strchr(command, '<') && ft_strchr(command, '>'))
		double_redir(big_struc, command);
	else if (ft_strchr(command, '<'))
		return (arrow_left(big_struc, parsed_command));
	//else if (ft_strchr(command, '<<'))
	//	heredoc(big_struc, command);
	else if (ft_strchr(command, '>') || ft_strstr(command, ">>"))
		return (arrow_right(big_struc, parsed_command));*/
	arrow_right(big_struc, parsed_command);
	return (0);
}
