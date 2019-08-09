/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/11 08:44:55 by lubenard          #+#    #+#             */
/*   Updated: 2019/08/09 17:11:55 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh21.h>

int		exec_external_command(t_hustru *big_struc, char *command)
{
	char	*path;
	char	**argv;

	argv = ft_strsplit(command, ' ');
	if (!(path = find_path(big_struc->path, argv[0])))
	{
		printf("j'affiche NULL\n");
		free(path);
		ft_deltab(argv);
		invalid_command(extract_first(command, ' '));
		printf("j'ai bien tout free\n");
		return (1);
	}
	printf("path = %s\n", path);
	exec_command_gen(path, argv, compact_env(big_struc->lkd_env));
	return (0);
}

int		basic_command(t_hustru *big_struc, char *command)
{
	char	*extract;
	int		ret_code;

	extract = extract_first(command, ' ');
	if (!ft_strcmp(extract, "env"))
		ret_code = print_env(big_struc, command);
	else if (!ft_strcmp(extract, "setenv"))
		ret_code = set_env(big_struc->lkd_env, command);
	else if (!ft_strcmp(extract, "unsetenv"))
		ret_code = unset_env(big_struc, command);
	else if (!ft_strcmp(extract, "echo"))
		ret_code = ft_echo(big_struc, command);
	else if (!ft_strcmp(extract, "cd"))
		ret_code = cd(big_struc, command);
	else if (!ft_strcmp(extract, "history"))
		ret_code = history(big_struc->lkd_hist);
	else if (!ft_strcmp(extract, "exit"))
		ret_code = find_exit(command, big_struc);
	else
		ret_code = exec_external_command(big_struc, command);
	free(extract);
	return (ret_code);
}

int		decide_commande(t_hustru *big_struc, char *command)
{
	if (!ft_strchr(command, '>') &&
		!ft_strchr(command, '<') && !ft_strchr(command, '|'))
		basic_command(big_struc, command);
	else if (!ft_strchr(command, '>') && !ft_strchr(command, '<') &&
		ft_strchr(command, '|'))
		handle_pipe(big_struc, command);
	else if ((ft_strchr(command, '>') || ft_strchr(command, '<')) &&
		!ft_strchr(command, '|'))
		redirections(big_struc, command);
	else if ((ft_strchr(command, '>') || ft_strchr(command, '<')) &&
		ft_strchr(command, '|'))
		redir_and_pipe(big_struc, command);
	return (0);
}

int		parser(t_hustru *big_struc, char *command)
{
	char	**semicolon;
	int		i;
	char	*trimmed_str;

	i = 0;
	semicolon = ft_strsplit(command, ';');
	while (semicolon[i])
		printf("Mon maillon vaut |%s|\n", semicolon[i++]);
	i = 0;
	while (semicolon[i])
	{
		trimmed_str = ft_strtrim(semicolon[i++]);
		big_struc->last_ret = decide_commande(big_struc, trimmed_str);
		free(trimmed_str);
	}
	i = 0;
	while (semicolon[i])
		free(semicolon[i++]);
	free(semicolon);
	free(command);
	return (0);
}
