/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/11 08:44:55 by lubenard          #+#    #+#             */
/*   Updated: 2019/09/15 14:57:05 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh21.h>

int		exec_external_command(t_hustru *big_struc, char **command)
{
	char	*path;

	if (!(path = find_path(big_struc->path, command[0])))
	{
		free(path);
		invalid_command(command[0]);
		return (1);
	}
	printf("path = %s\n", path);
	exec_command_gen(path, command, compact_env(big_struc->lkd_env));
	return (0);
}

int		basic_command(t_hustru *big_struc, char **command)
{
	int		ret_code;

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
	{
		printf("Ma commande est une commande generale\n");
		ret_code = exec_external_command(big_struc, command);
	}
	printf("Mon code de retour est %d\n", ret_code);
	return (ret_code);
}

char	**parse_line(t_hustru *big_struc, char **command)
{
	int i;
	int e;
	char *tmp;

	e = 0;
	i = 0;
	while (command[i])
	{
		if (command[i][0] == '$')
		{
			tmp = handle_dollar(big_struc, command[i]);
			printf("je remplace $\n");
			free(command[i]);
			command[i] = tmp;
		}
		if (command[i][0] == '~')
		{
			tmp = handle_tilde(big_struc, command[i]);
			printf("je remplace ~\n");
			free(command[i]);
			command[i] = tmp;
		}
		if (tmp == NULL)
		{
			ft_putstr(command[0]);
			ft_putendl_fd(" : Error due to environ", 2);
			ft_deltab(command);
			return (NULL);
		}
		i++;
	}
	return (command);
}

int		decide_commande(t_hustru *big_struc, char **command)
{
	if (!ft_tabchr(command, '>') &&
			!ft_tabchr(command, '<') && !ft_tabchr(command, '|'))
		return (basic_command(big_struc, command));
	else if (!ft_tabchr(command, '>') && !ft_tabchr(command, '<') &&
			ft_tabchr(command, '|'))
		return (handle_pipe(big_struc, big_struc->line));
	else if ((ft_tabchr(command, '>') || ft_tabchr(command, '<')) &&
			!ft_tabchr(command, '|'))
		redirections(big_struc, big_struc->line, command);
	else if ((ft_tabchr(command, '>') || ft_tabchr(command, '<')) &&
			ft_tabchr(command, '|'))
		redir_and_pipe(big_struc, command);
	return (0);
}

int		parser(t_hustru *big_struc, char *command)
{
	char	**semicolon;
	int		i;
	char	**split_space;
	int		e;

	(void)big_struc;
	i = 0;
	e = 0;
	semicolon = ft_strsplit(command, ';');
	while (semicolon[i])
		printf("Mon maillon vaut |%s|\n", semicolon[i++]);
	i = 0;
	while (semicolon[i])
	{
		big_struc->line = semicolon[i];
		split_space = parse_line(big_struc, ft_strsplit(semicolon[i++], ' '));
		if (split_space == NULL)
		{
			ft_deltab(semicolon);
			free(command);
			return (1);
		}
		big_struc->last_ret = decide_commande(big_struc, split_space);
		ft_deltab(split_space);
	}
	ft_deltab(semicolon);
	free(command);
	return (0);
}
