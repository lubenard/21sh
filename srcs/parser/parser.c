/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/11 08:44:55 by lubenard          #+#    #+#             */
/*   Updated: 2019/10/21 16:47:15 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh21.h>

int		is_between_quotes(char *command, int quote_mode)
{
	if (command[0] != '\''
	&& command[ft_strlen(command) - 1] != '\''
	&& quote_mode == 1)
		return (0);
	else if (command[0] != '\"'
	&& command[ft_strlen(command) - 1] != '\"'
	&& quote_mode == 2)
		return (0);
	else if (command[0] != '\''
	&& command[ft_strlen(command) - 1] != '\''
	&& command[0] != '\"'
	&& command[ft_strlen(command) - 1] != '\"'
	&& quote_mode == 3)
		return (0);
	return (1);
}

int		is_between_quotes2(char **command, char quote_char)
{
	int i;

	i = 0;
	while (command[i])
	{
		if (ft_strchr(command[i], quote_char) && !ft_strchr(command[i], '\'')
		&& !ft_strchr(command[i], '\"'))
			return (0);
		else if (ft_strchr(command[i], quote_char)
		&& (ft_strchr(command[i], '\'')
		|| ft_strchr(command[i], '\"')))
			return (1);
		i++;
	}
	return (0);
}

void	remove_quote(char ***command)
{
	int		i;
	int		e;
	int		j;
	char	*tmp;

	j = 0;
	while ((*command)[j])
	{
		i = 0;
		e = 0;
		if (ft_strchr((*command)[j], '\'') || ft_strchr((*command)[j], '\"'))
		{
			while ((*command)[j][i])
			{
				if ((*command)[j][i] != '\'' && (*command)[j][i] != '\"')
					e++;
				i++;
			}
			if (!(tmp = ft_strnew(e)))
				return ;
			e = 0;
			i = 0;
			while ((*command)[j][i])
			{
				if ((*command)[j][i] != '\'' && (*command)[j][i] != '\"')
					tmp[e++] = (*command)[j][i];
				i++;
			}
			free((*command)[j]);
			(*command)[j] = tmp;
		}
		j++;
	}
}

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
** Replace the ~ or the $ with his equivalence
*/

void	swap_elem(char **command, char *replace)
{
	free(*command);
	*command = replace;
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
		if (!is_between_quotes(command[i], 1))
		{
			if (ft_strchr(command[i], '$'))
				swap_elem(&command[i],
				handle_dollar(big_struc, command[i]));
		}
		if (!is_between_quotes(command[i], 3))
		{
			if (command[i] && ft_strchr(command[i], '~'))
				swap_elem(&command[i],
				handle_tilde(big_struc, command[i]));
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
	if (!ft_strcmp(command[0], ""))
		return (0);
	big_struc->line = recompact_command(command);
	if (ft_tabchr(command, '|') && !is_between_quotes2(command, '|'))
		ret = (should_fork) ? handle_pipe(big_struc, big_struc->line)
			: handle_pipe_w_fork(big_struc, big_struc->line);
	else if ((!is_between_quotes2(command, '<') && !is_between_quotes2(command, '>')
	&& (ft_tabchr(command, '>') || ft_tabchr(command, '<'))))
		ret = redirections(big_struc, command, should_fork);
	else
	{
		free(big_struc->line);
		return (ret = basic_command(big_struc, command, fun));
	}
	free(big_struc->line);
	return (ret);
}

char	**create_command(char **command, int *i, int *e)
{
	char	**ret;
	int		j;

	j = 0;
	while (command[*i] && ft_strcmp(command[*i], ";"))
		(*i)++;
	if (*i == 0)
	{
		(*i)++;
		if (!(ret = malloc(sizeof(char *) * 2)))
			return (NULL);
		ret[0] = "";
		return (ret);
	}
	if (!(ret = malloc(sizeof(char *) * (*i + 1))))
		return (NULL);
	while (*e != *i)
		ret[j++] = ft_strdup(command[(*e)++]);
	ret[j] = NULL;
	if (command[*i])
		(*i)++;
	return (ret);
}

/*
** Main parser function
** Will parse by quote then by space to launch correct command.
*/

int		parser(t_hustru *big_struc, char *command)
{
	char	**semicolon;
	char	**quoted_command;
	int		i;
	int		e;

	quoted_command = final_lexer(command);
	if (check_semic_error(quoted_command) == -1)
		return (big_struc->last_ret = 258);
	if (quoted_command && !ft_strcmp(quoted_command[0], ""))
	{
		ft_deltab(quoted_command);
		return ((big_struc->last_ret = 0));
	}
	parse_line(big_struc, quoted_command);
	e = 0;
	i = 0;
	while (quoted_command && quoted_command[i])
	{
		i++;
		semicolon = create_command(quoted_command, &i, &e);
		e = i;
		if (check_error_lexer(semicolon) == -1)
		{
			ft_deltab(semicolon);
			ft_strdel(&big_struc->pipe_heredoc);
			big_struc->should_heredoc = 1;
			continue ;
		}
		big_struc->last_ret = decide_commande(big_struc,
			semicolon, exec_command_gen, 1);
		ft_deltab(semicolon);
		ft_strdel(&big_struc->pipe_heredoc);
		big_struc->should_heredoc = 1;
	}
	if (quoted_command)
		ft_deltab(quoted_command);
	return (0);
}
