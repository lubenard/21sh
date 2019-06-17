/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/11 08:44:55 by lubenard          #+#    #+#             */
/*   Updated: 2019/06/17 22:30:35 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh21.h>

int		basic_command(t_hustru *big_struc, char *command)
{
	char *extract;

	extract = extract_first(command, ' ');
	if (!ft_strcmp(extract, "env"))
		print_env(big_struc, command);
	else if (!ft_strcmp(extract, "setenv"))
		set_env(big_struc->lkd_env, command);
	else if (!ft_strcmp(extract, "unsetenv"))
		unset_env(big_struc, command);
	else if (!ft_strcmp(extract, "echo"))
		ft_echo(big_struc, command);
	else if (!ft_strcmp(extract, "cd"))
		cd(big_struc, command);
	free(extract);
	return(0);
}

int		decide_commande(t_hustru *big_struc, char *command)
{
	if (!ft_strchr(command, '>') && 
		!ft_strchr(command, '<') && !ft_strchr(command, '|'))
		basic_command(big_struc, command);
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
