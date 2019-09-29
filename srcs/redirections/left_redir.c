/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   left_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/17 15:59:55 by lubenard          #+#    #+#             */
/*   Updated: 2019/09/29 18:20:08 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh21.h>

/*
** Send into input programm
*/

int		arrow_left(t_hustru *big_struc, char **command)
{
	int i;
	char	**tab;

	(void)big_struc;
	i = 0;
	while (command[i] && !ft_strchr(command[i], '<'))
		i++;
	if (!(tab = create_command(command, i, '<')))
		return (1);
	return (0);
}
