/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd2.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/03 15:13:49 by lubenard          #+#    #+#             */
/*   Updated: 2019/06/13 21:09:54 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh21.h>

char	*extract_path(char *command)
{
	int i;
	int e;

	if (!ft_strcmp(command, ".."))
		return (ft_strdup(".."));
	i = 0;
	e = 0;
	while (command[i] == ' ' || command[i] == '\t')
		i++;
	while (command[i] && command[i] != ' ')
		i++;
	while (command[i] == ' ' || command[i] == '\t')
		i++;
	while (command[i + e])
		e++;
	return (ft_strsub(command, i, e));
}