/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/11 08:44:55 by lubenard          #+#    #+#             */
/*   Updated: 2019/09/30 16:56:29 by lubenard         ###   ########.fr       */
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

	//remplacer par un tableau de pointeur sur fonction (a voir)
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
		ret_code = fun(big_struc, command);
	}
	printf("Mon code de retour est %d\n", ret_code);
	return (ret_code);
}

/*
** Replace the ~ or the $ with his equivalence
*/

void	swap_elem(char **command, char *replace)
{
	printf("Je remplace %s par %s\n", *command, replace);
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
	while (command[i])
	{
		if (command[i][0] == '$')
			swap_elem(&command[i],
			handle_dollar(big_struc, command[i]));
		if (command[i] && command[i][0] == '~')
			swap_elem(&command[i],
			handle_tilde(big_struc, command[i]));
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

int		decide_commande(t_hustru *big_struc, char **command)
{
	if (!ft_tabchr(command, '>') &&
			!ft_tabchr(command, '<') && !ft_tabchr(command, '|'))
		return (basic_command(big_struc, command, exec_command_gen));
	else if (!ft_tabchr(command, '>') && !ft_tabchr(command, '<') &&
			ft_tabchr(command, '|'))
		return (handle_pipe(big_struc, big_struc->line));
	else if ((ft_tabchr(command, '>') || ft_tabchr(command, '<')) &&
			!ft_tabchr(command, '|'))
		return (redirections(big_struc, big_struc->line));
	else if ((ft_tabchr(command, '>') || ft_tabchr(command, '<')) &&
			ft_tabchr(command, '|'))
		redir_and_pipe(big_struc, command);
	return (0);
}

/*
** Main parser function
** Will split by semicolon then by space to launch correct command.
*/

int		parser(t_hustru *big_struc, char *command)
{
	char	**semicolon;
	int		i;
	char	**split_space;
	int		e;

	i = 0;
	if (!command)
		return ((big_struc->last_ret = 1));
	semicolon = ft_strsplit(command, ';');
	while (semicolon[i])
	{
		printf("\e[32mJ'execute cette ligne |%s|\e[0m\n", semicolon[i]);
		big_struc->line = semicolon[i];
		split_space = parse_line(big_struc, ft_strsplit(semicolon[i++], ' '));
		e = 0; // This variable is only for debug
		while (split_space[e])
			printf("\e[33mDecoupe en espace, cela donne |%s|\e[0m\n", split_space[e++]);
		big_struc->last_ret = decide_commande(big_struc, split_space);
		ft_deltab(split_space);
	}
	ft_deltab(semicolon);
	return (0);
}
