/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/15 11:59:46 by lubenard          #+#    #+#             */
/*   Updated: 2019/10/20 21:18:20 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh21.h>

void	handle_tilde2(char user_name[4096], char *command, int i)
{
	if (i != 1)
		ft_strnncpy(user_name, command, i, ft_strlen(command) - 1);
	else
		ft_stricpy(user_name, command, i);
}

void	handle_echo_options(char option)
{
	if (option == 'a')
		ft_putchar('\a');
	else if (option == 'b')
		ft_putchar('\b');
	else if (option == 'f')
		ft_putchar('\f');
	else if (option == 'n')
		ft_putchar('\n');
	else if (option == 'r')
		ft_putchar('\r');
	else if (option == 't')
		ft_putchar('\t');
	else if (option == 'v')
		ft_putchar('\v');
}

void	ft_putstr_echo(char *str)
{
	int		e;

	e = 0;
	while (str[e])
	{
		if (str[e] == '\\')
		{
			if (str[e + 1] == '\\')
			{
				handle_echo_options(str[e + 2]);
				e += 3;
			}
			else
				e++;
		}
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
