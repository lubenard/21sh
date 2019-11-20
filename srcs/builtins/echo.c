/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/15 11:59:46 by lubenard          #+#    #+#             */
/*   Updated: 2019/11/20 11:58:02 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh21.h>

void	ft_putstr_echo(char *str)
{
	int		e;

	e = 0;
	while (str && str[e])
	{
		if (str[e] == '\\')
			e++;
		else
			ft_putchar(str[e++]);
	}
}

int		ft_echo(t_hustru *big_struc, char **command)
{
	int		e;
	int		i;

	i = 1;
	e = (!ft_strcmp(command[1], "-n")) ? 1 : 0;
	while (command[i + e])
	{
		if (ft_strcmp(command[i + e], ""))
		{
			ft_putstr_echo(command[i + e]);
			if (command[i + e + 1] && !ft_strchr(command[i + e + 1], '>')
			&& !ft_strchr(command[i + e + 1], '<')
			&& !ft_strchr(command[i + e + 1], '|'))
				ft_putchar(' ');
		}
		i++;
	}
	if (e == 0)
		ft_putchar('\n');
	return (big_struc->last_ret);
}
