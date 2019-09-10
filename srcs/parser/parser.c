/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/11 08:44:55 by lubenard          #+#    #+#             */
/*   Updated: 2019/09/10 18:57:26 by lubenard         ###   ########.fr       */
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
		ret_code = exec_external_command(big_struc, command);
	return (ret_code);
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

void	parse_command(char tmp[25000])
{
	int i = 0;
	char tmp2;
	int e = 0;

	printf("String before |%s|\n", tmp);
	while (tmp[i])
	{
		if (tmp[i] == '>')
		{
			printf("Je trouve bien un cas, et tmp[i - 1] vaut %c\n", tmp[i - 1]);
			if (ft_isalpha(tmp[i - 1]) || (ft_isdigit(tmp[i - 1] && tmp[i - 2] != ' ')))
			{
				tmp2 = tmp[i - 1];
				printf("Tmp2 vaut |%c|\n", tmp2);
				tmp[i - 1] = ' ';
				printf("tmp[%d - 1] vaut %c\n", i, tmp[i-1]);
				e = i;
				while (tmp[e])
				{
					tmp[e] = tmp2;
					tmp2 = tmp[e + 1];
					printf("Tmp2 vaut |%c|\n", tmp2);
					e++;
				}
				break ;
			}
		}
		i++;
	}
	printf("String after |%s|\n", tmp);
}

int		parser(t_hustru *big_struc, char *command)
{
	char	**semicolon;
	int		i;
//	char	**split_space;
	int		e;
	char	tmp[25000]; //A voir

	(void)big_struc;
	i = 0;
	e = 0;
	semicolon = ft_strsplit(command, ';');
	while (semicolon[i])
		printf("Mon maillon vaut |%s|\n", semicolon[i++]);
	i = 0;
	while (semicolon[i])
	{
		ft_strcpy(tmp, semicolon[i]);
		parse_command(tmp);
		/*big_struc->line = semicolon[i];
		  split_space = ft_strsplit(semicolon[i++], ' ');
		  big_struc->last_ret = decide_commande(big_struc, split_space);
		  ft_deltab(split_space);*/
		i++;
	}
	//ft_deltab(semicolon);
	//free(command);
	return (0);
}
