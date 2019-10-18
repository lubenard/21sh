/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/11 08:44:55 by lubenard          #+#    #+#             */
/*   Updated: 2019/10/18 16:09:53 by lubenard         ###   ########.fr       */
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
		{
			return (0);
		}
		else if (ft_strchr(command[i], quote_char) && (ft_strchr(command[i], '\'')
		|| ft_strchr(command[i], '\"')))
		{
			return (1);
		}
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
			printf("Je malloc de %d\n", e);
			e = 0;
			i = 0;
			while ((*command)[j][i])
			{
				if ((*command)[j][i] != '\'' && (*command)[j][i] != '\"')
				{
					tmp[e++] = (*command)[j][i];
				}
				i++;
			}
			free((*command)[j]);
			(*command)[j] = tmp;
			printf("Tmp = %s\n", tmp);
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

	if (should_fork)
		printf("Je dois fork");
	else
		printf("Je ne fork pas\n");
	int k = 0; // This variable is only for debug
	while (command[k])
		printf("\e[32mJ'execute |%s|\e[0m\n", command[k++]);
	ret = 0;
	if (!ft_strcmp(command[0], ""))
		return (0);
	big_struc->line = recompact_command(command);
	if (ft_tabchr(command, '|') && !is_between_quotes2(command, '|'))
	{
		printf("Je rentre dans les pipe !\n");
		if (should_fork)
			ret = handle_pipe(big_struc, big_struc->line);
		else
			ret = handle_pipe_w_fork(big_struc, big_struc->line);
	}
	else if ((!is_between_quotes2(command, '<') && !is_between_quotes2(command, '>')
	&& (ft_tabchr(command, '>') || ft_tabchr(command, '<'))))
	{
		printf("Je rentre dans les redirections\n");
		if (should_fork)
			ret = redirections(big_struc, command);
		else
			ret = redirections_w_fork(big_struc, command);
	}
	else
	{
		free(big_struc->line);
		ret = basic_command(big_struc, command, fun);
		return (ret);
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
	if (check_error_lexer(quoted_command) == -1)
		return (big_struc->last_ret = 258);
	/*i = 0;
	while (quoted_command[i])
		printf("\e[31mDecoupe en quote, cela donne |%s|\e[0m\n", quoted_command[i++]);
	printf("\e[31mDecoupe en quote, cela donne |%s|\e[0m\n", quoted_command[i]);*/
	if (quoted_command && !ft_strcmp(quoted_command[0], ""))
	{
		ft_deltab(quoted_command);
		return ((big_struc->last_ret = 0));
	}
	//if (check_command(quoted_command))
	//	return (big_struc->last_ret = 258);
	parse_line(big_struc, quoted_command);
	/*i = 0;
	while (quoted_command[i])
		printf("\e[33mDecoupe en quote apres traitement, cela donne |%s|\e[0m\n", quoted_command[i++]);
	printf("\e[33mDecoupe en quote apres traitement, cela donne |%s|\e[0m\n", quoted_command[i]);*/
	e = 0;
	i = 0;
	while (quoted_command && quoted_command[i])
	{
		i++;
		semicolon = create_command(quoted_command, &i, &e);
		/*int m = 0;
		while (semicolon[m])
			printf("\e[31mDecoupe en quote, cela donne |%s|\e[0m\n", semicolon[m++]);
		printf("\e[31mDecoupe en quote, cela donne |%s|\e[0m\n", semicolon[m]);*/
		e = i;
		big_struc->last_ret = decide_commande(big_struc, semicolon, exec_command_gen, 1);
		//if (big_struc->last_ret > 0)
			ft_deltab(semicolon);
	}
	if (quoted_command)
		ft_deltab(quoted_command);
	return (0);
}
