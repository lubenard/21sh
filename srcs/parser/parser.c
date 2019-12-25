/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/11 08:44:55 by lubenard          #+#    #+#             */
/*   Updated: 2019/12/25 16:57:20 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh21.h>

/*
** Decide if the command is a bultin or not
*/

int		basic_command(t_hustru *big_struc, char **command,
	int (*fun)(t_hustru *, char **))
{
	int		ret_code;

	remove_quote(&command);
	if (!ft_strcmp(command[0], "env"))
		ret_code = print_env(big_struc, command);
	else if (!ft_strcmp(command[0], "setenv"))
		ret_code = set_env(big_struc, command);
	else if (!ft_strcmp(command[0], "unsetenv"))
		ret_code = unset_env(big_struc, command);
	else if (!ft_strcmp(command[0], "echo"))
		ret_code = ft_echo(big_struc, command);
	else if (!ft_strcmp(command[0], "cd"))
		ret_code = cd(big_struc, command);
	else if (!ft_strcmp(command[0], "history"))
		ret_code = history(big_struc->lkd_hist);
	else if (!ft_strcmp(command[0], "exit"))
		ret_code = find_exit(big_struc, command);
	else
		ret_code = fun(big_struc, command);
	return (ret_code);
}

/*
** This function will replace ~ and $ by their equivalent
** in the env or by the correct path.
*/

char	**parse_line(t_hustru *big_struc, char **command)
{
	int		i;
	int		e;

	e = 0;
	i = 0;
	while (command && command[i])
	{
		if (!is_between_quotes(command[i], 3))
		{
			if (command[i] && ft_strchr(command[i], '~'))
				swap_elem(&command[i],
				handle_tilde(big_struc, command[i]));
		}
		if (!is_between_quotes(command[i], 1))
		{
			if (ft_strchr(command[i], '$'))
				swap_elem(&command[i],
				handle_dollar(big_struc, command[i]));
		}
		if (command[i] == NULL)
			command[i] = ft_strdup("");
		i++;
	}
	return (command);
}

/*
** Decide if the command contains a redirections, pipe,
** or if it is juste a normal command.
*/

int		decide_commande(t_hustru *big_struc, char **command,
	int (*fun)(t_hustru *, char **), int should_fork)
{
	int ret;

	ret = 0;
	if (check_semic_error(command) == -1 || check_error_lexer(command) == -1)
		return (258);
	if (!command[0] || !ft_strcmp(command[0], ""))
		return (0);
	if (should_fork)
		big_struc->line = recompact_command(command);
	if (ft_tabchr(command, '|')
	&& !is_between_quotes2(command, '|') && should_fork)
		ret = handle_pipe(big_struc, big_struc->line);
	else if ((!is_between_quotes2(command, '<')
	&& !is_between_quotes2(command, '>')
	&& (ft_tabchr(command, '>') || ft_tabchr(command, '<'))))
		ret = redirections(big_struc, command, should_fork);
	else
	{
		if (should_fork)
			ft_strdel(&big_struc->line);
		return (ret = basic_command(big_struc, command, fun));
	}
	if (should_fork)
		free(big_struc->line);
	return (ret);
}

void	parser_loop(t_hustru *big_struc, char **quoted_command)
{
	int		i;
	int		e;
	char	**semicolon;

	e = 0;
	i = 0;
	while (quoted_command && quoted_command[i])
	{
		i++;
		semicolon = create_command(quoted_command, &i, &e);
		semicolon = parse_line(big_struc, semicolon);
		e = i;
		big_struc->last_ret = decide_commande(big_struc,
			semicolon, exec_command_gen, 1);
		ft_deltab(&semicolon);
		ft_strdel(&big_struc->pipe_heredoc);
		big_struc->should_heredoc = 1;
	}
}

/*
** Main parser function
** Will parse by quote then by space to launch correct command.
*/

int		parser(t_hustru *big_struc, char *command)
{
	char	**quoted_command;

	if (command && !ft_strisascii(command))
	{
		ft_putstr("Invalid character detected\n");
		return (1);
	}
	quoted_command = final_lexer(command);
	if (quoted_command && !ft_strcmp(quoted_command[0], ""))
	{
		ft_deltab(&quoted_command);
		return ((big_struc->last_ret = 0));
	}
	parser_loop(big_struc, quoted_command);
	if (quoted_command)
		ft_deltab(&quoted_command);
	return (0);
}
