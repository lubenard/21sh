/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/16 17:57:01 by lubenard          #+#    #+#             */
/*   Updated: 2019/09/26 16:41:18 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh21.h>

/*
** NOTES : arrow is creating the files before executing command
*/

void	redir_and_pipe(t_hustru *big_struc, char **command)
{
	char **arg;
	int i = 0;
	int		link[2];
	pid_t	pid;
	char	output[50000];
	int		wait_pid;

	(void)command;
	(void)big_struc;
	arg = NULL;
//	arg = ft_strsplit_redir(command[0], '>');
	while (arg[i])
		printf("Element vaut %s\n", arg[i++]);
	if (pipe(link) == -1 || (pid = fork()) == -1)
		return ;
	if (pid == 0)
	{
		dup2(link[1], 1);
		close(link[0]);
		close(link[1]);
		handle_pipe(big_struc, arg[0]);
		exit(0);
	}
	else
	{
		while ((wait_pid = wait(&pid)) > 0)
			;
		close(link[1]);
		read(link[0], output, 50000);
		printf("Output vaut |%s|\n", output);
	}
	save_redir(big_struc->line, ft_strndup(output, ft_strlen(output) - 1));
}

void	double_redir(t_hustru *big_struc, char *command)
{
	int		link[2];
	pid_t	pid;
	char	output[50000];
	int		wait_pid;

	if (pipe(link) == -1 || (pid = fork()) == -1)
		return ;
	if (pid == 0)
	{
		dup2(link[1], 1);
		close(link[0]);
		close(link[1]);
		arrow_left(big_struc, extract_first(command, '>'));
		exit(0);
	}
	else
	{
		while ((wait_pid = wait(&pid)) > 0)
			;
		close(link[1]);
		read(link[0], output, 50000);
	}
	save_redir(big_struc->line, ft_strndup(output, ft_strlen(output) - 1));
}

int		redirections(t_hustru *big_struc, char *command)
{
	(void)big_struc;
	(void)command;
	char **parsed_command;
	int i = 0; //used for debug online

	parsed_command = parse_redir(command);
	while (parsed_command[i])
		printf("[Parsed redir] %s\n", parsed_command[i++]);
	if (ft_strchr(command, '<') && ft_strchr(command, '>'))
		double_redir(big_struc, command);
	else if (ft_strchr(command, '<'))
		arrow_left(big_struc, command);
	//else if (ft_strchr(command, '<<'))
	//	double_arrow_left(big_struc, command);
	else if (ft_strchr(command, '>') || ft_strstr(command, ">>"))
		return (arrow_right(big_struc, parsed_command));
	return (0);
}
