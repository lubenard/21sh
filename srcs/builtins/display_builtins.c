/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_builtins.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/15 17:03:58 by lubenard          #+#    #+#             */
/*   Updated: 2019/05/15 17:05:16 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../sh21.h"

char	*error_setenv(char *command, int i, int e)
{
	int k;

	if (ft_strrchr(command, i, ' ') != NULL)
	{
		ft_putstr_fd("setenv: invalid syntax\n", 2);
		ft_putstr_fd("the correct syntax is t=1\n", 2);
		return (NULL);
	}
	k = i;
	while (command[k])
	{
		if (!ft_isascii(command[k]) || command[k] == '\t'
		|| command[k] == '"' || command[k] == '\'')
		{
			ft_putstr_fd("setenv: invalid syntax\n", 2);
			ft_putstr_fd("Invalid character\n", 2);
			return (NULL);
		}
		k++;
	}
	return (ft_strsub(command, i, e));
}

