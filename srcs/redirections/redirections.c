/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/16 17:57:01 by lubenard          #+#    #+#             */
/*   Updated: 2019/12/16 13:56:07 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh21.h>

int		is_builtin(char *command)
{
	if (!ft_strcmp(command, "env"))
		return (1);
	else if (!ft_strcmp(command, "setenv"))
		return (1);
	else if (!ft_strcmp(command, "unsetenv"))
		return (1);
	else if (!ft_strcmp(command, "echo"))
		return (1);
	else if (!ft_strcmp(command, "cd"))
		return (1);
	else if (!ft_strcmp(command, "history"))
		return (1);
	else if (!ft_strcmp(command, "exit"))
		return (1);
	return (0);
}

int		builtin_redir(t_hustru *big_struc, char **lexed_command)
{
	int stdin_copy;
	int stdout_copy;
	int stderr_copy;
	int ret_code;

	stdin_copy = dup(0);
	stdout_copy = dup(1);
	stderr_copy = dup(2);
	ret_code = launch_arrow_w_fork(big_struc, lexed_command);
	dup2(stdin_copy, 0);
	dup2(stdout_copy, 1);
	dup2(stderr_copy, 2);
	return (ret_code);
}

int		redirections(t_hustru *big_struc, char **lexed_command, int should_fork)
{
	int ret_code;

	ret_code = 0;
	if (!should_fork)
		return (launch_arrow_w_fork(big_struc, lexed_command));
	else if (is_builtin(lexed_command[0]))
		return (builtin_redir(big_struc, lexed_command));
	return (launch_arrow(big_struc, lexed_command));
}
