/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/11 08:44:55 by lubenard          #+#    #+#             */
/*   Updated: 2019/10/14 21:43:02 by lubenard         ###   ########.fr       */
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
		//printf("Ma commande est une commande generale\n");
		ret_code = fun(big_struc, command);
	}
	//printf("Mon code de retour est %d\n", ret_code);
	return (ret_code);
}

/*
** Replace the ~ or the $ with his equivalence
*/

void	swap_elem(char **command, char *replace)
{
	//printf("Je remplace %s par %s\n", *command, replace);
	free(*command);
	*command = replace;
}

/*
** This function will replace ~ and $ by their equivalent
** in the env or by the correct path.
*/

char	*remove_quote(char *command)
{
	char *copy;

	copy = NULL;
	if ((command[0] == '\"' && command[ft_strlen(command) - 1] == '\"')
	|| (command[0] == '\'' && command[ft_strlen(command) - 1] == '\''))
	{
		if (!(copy = ft_strnew(ft_strlen(command) - 2)))
			return (0);
		ft_strnncpy(copy, command, 1, ft_strlen(command) - 1);
	}
	else
		return (ft_strdup(command));
	return (copy);
}

char	**parse_line(t_hustru *big_struc, char **command)
{
	int		i;
	int		e;

	e = 0;
	i = 0;
	while (command[i])
	{
		if (command[i][0] != '\''
		&& command[i][ft_strlen(command[i]) - 1] != '\'')
		{
			if (ft_strchr(command[i],'$'))
				swap_elem(&command[i],
				handle_dollar(big_struc, command[i]));
			if (command[i] && ft_strchr(command[i], '~'))
				swap_elem(&command[i],
				handle_tilde(big_struc, command[i]));
			if (command[i] == NULL)
				command[i] = ft_strdup("");
		}
		else
			swap_elem(&command[i], remove_quote(command[i]));
		i++;
	}
	return (command);
}

/*
** Decide if the command contains a redirections, pipe,
** or if it is juste a normal command.
*/

int		decide_commande(t_hustru *big_struc, char **command, int (*fun)(t_hustru *, char **))
{
	//int k = 0; // This variable is only for debug
	big_struc->line = recompact_command(command);
	//while (command[k])
	//	printf("\e[32mJ'execute |%s|\e[0m\n", command[k++]);
	if (!ft_strcmp(command[0], ""))
		return (0);
	if (ft_tabchr(command, '|') && !ft_tabchr(command, '<'))
	{
	//	printf("Je rentre dans les pipe !\n");
		return (handle_pipe(big_struc, big_struc->line));
	}
	else if ((ft_tabchr(command, '>') || ft_tabchr(command, '<')))
	{
	//	printf("Je rentre dans les redirections\n");
		return (redirections(big_struc, big_struc->line));
	}
	else if (!ft_tabchr(command, '>') &&
			!ft_tabchr(command, '<') && !ft_tabchr(command, '|'))
		return (basic_command(big_struc, command, fun));
	return (0);
}

int		check_command(char **command)
{
	int i;

	i = 0;
	while (command[i])
	{
		if (((command[i][0] != '\''
		&& command[i][ft_strlen(command[i]) - 1] != '\'')
		&& (command[i][0] != '\"'
		&& command[i][ft_strlen(command[i]) - 1] != '\"'))
		&& ft_occur(command[i], ';') >= 2)
		{
			ft_putendl_fd("ymarsh: syntax error near unexpected token `;;'", 2);
			ft_deltab(command);
			return (0);
		}
		i++;
	}
	return (1);
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
		ret[j++] = remove_quote(command[(*e)++]);
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

	quoted_command = parse_quote(command);
	/*i = 0;
	while (quoted_command[i])
		printf("\e[31mDecoupe en quote, cela donne |%s|\e[0m\n", quoted_command[i++]);
	printf("\e[31mDecoupe en quote, cela donne |%s|\e[0m\n", quoted_command[i]);*/
	if (!ft_strcmp(quoted_command[0], ""))
	{
		ft_deltab(quoted_command);
		return ((big_struc->last_ret = 0));
	}
	if (!check_command(quoted_command))
		return (big_struc->last_ret = 258);
	parse_line(big_struc, quoted_command);
	/*i = 0;
	while (quoted_command[i])
		printf("\e[33mDecoupe en quote apres traitement, cela donne |%s|\e[0m\n", quoted_command[i++]);
	printf("\e[33mDecoupe en quote apres traitement, cela donne |%s|\e[0m\n", quoted_command[i]);*/
	e = 0;
	i = 0;
	while (quoted_command[i])
	{
		//printf("JE LANCE DEPUIS LE MAIN\n");
		semicolon = create_command(quoted_command, &i, &e);
		e = i;
		big_struc->last_ret = decide_commande(big_struc, semicolon, exec_command_gen);
		free(big_struc->line);
		ft_deltab(semicolon);
	}
	ft_deltab(quoted_command);
	return (0);
}
