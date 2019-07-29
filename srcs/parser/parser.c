/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/11 08:44:55 by lubenard          #+#    #+#             */
/*   Updated: 2019/07/29 14:19:26 by lubenard         ###   ########.fr       */
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
		invalid_command(command);
		printf("j'ai bien tout free\n");
		return (1);
	}
	printf("path = %s\n", path);
	exec_command_gen(path,argv, compact_env(big_struc->lkd_env));
	return (0);
}

int		basic_command(t_hustru *big_struc, char *command)
{
	char	*extract;
	int		ret_code;
	char	*trimmed_str;

	//printf("untrimmed str: |%s|\n",command);
	trimmed_str = ft_strtrim(command);
	//printf("trimmed str |%s|\n",trimmed_str);
	extract = extract_first(trimmed_str, ' ');
	//printf("extract vaut '%s'\n",extract);
	if (!ft_strcmp(extract, "env"))
		ret_code = print_env(big_struc, trimmed_str);
	else if (!ft_strcmp(extract, "setenv"))
		ret_code = set_env(big_struc->lkd_env, trimmed_str);
	else if (!ft_strcmp(extract, "unsetenv"))
		ret_code = unset_env(big_struc, trimmed_str);
	else if (!ft_strcmp(extract, "echo"))
		ret_code = ft_echo(big_struc, trimmed_str);
	else if (!ft_strcmp(extract, "cd"))
		ret_code = cd(big_struc, trimmed_str);
	else
		ret_code = exec_external_command(big_struc, trimmed_str);
	free(extract);
	free(trimmed_str);
	return(ret_code);
}

int		decide_commande(t_hustru *big_struc, char *command)
{
	if (!ft_strchr(command, '>') &&
		!ft_strchr(command, '<') && !ft_strchr(command, '|'))
		basic_command(big_struc, command);
	else if (!ft_strchr(command, '>') && !ft_strchr(command, '<') &&
		ft_strchr(command, '|'))
		handle_pipe(big_struc->lkd_env, big_struc->path, command);
	else if ((ft_strchr(command, '>') || ft_strchr(command, '<')) &&
		!ft_strchr(command, '|'))
		redirections(big_struc->lkd_env, big_struc->path, command);
	else
		printf("Je regarde %s\n", command);
	return (0);
}

int		parser(t_hustru *big_struc, char *command)
{
	char	**semicolon;
	int		i;

	i = 0;
	semicolon = ft_strsplit(command, ';');
	while (semicolon[i])
		big_struc->last_ret = decide_commande(big_struc, semicolon[i++]);
	i = 0;
	while (semicolon[i])
		free(semicolon[i++]);
	free(semicolon);
	free(command);
	return (0);
}
