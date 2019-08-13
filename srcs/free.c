/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/03 17:01:28 by lubenard          #+#    #+#             */
/*   Updated: 2019/08/13 19:49:59 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

int		free_after_exec(char *get_right_path, char **argv,
	char **env)
{
	ft_deltab(argv);
	free(get_right_path);
	//free(argv);
	free(env);
	return (0);
}

char	*extract_command(char *command)
{
	int i;
	int e;

	i = 0;
	e = 0;
	while (command[e] == ' ' || command[e] == '\t')
		e++;
	while (ft_isalnum(command[i + e])
	|| command[i + e] == '.' || command[i + e] == '/')
		++i;
	return (ft_strlower(ft_strsub(command, e, i)));
}
