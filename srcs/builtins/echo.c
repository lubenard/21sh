/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/15 11:59:46 by lubenard          #+#    #+#             */
/*   Updated: 2019/06/14 15:44:42 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh21.h>

int		handle_dollar(t_hustru *big_struc, char *command, int i)
{
	int		e;
	char	*str;

	e = 0;
	if (command[i] == '$' && command[i + 1] != ' ')
	{
		if (command[i + 1] == '?')
		{
			ft_putnbr(big_struc->last_ret);
			return (i + 1);
		}
		i++;
		while (command[i + e] && command[i + e] != ' '
		&& ft_isalnum(command[i + e]))
			e++;
		str = find_in_env(big_struc->lkd_env, ft_strsub(command, i, e));
		ft_putstr(str);
		free(str);
		return (i + e);
	}
	return (i + 1);
}

int		verify_folder(char buffer[4096], char user_name[33], char *str)
{
	struct stat		s;
	int				err;

	free(str);
	ft_strcat(buffer, user_name);
	err = stat(buffer, &s);
	if (err == -1)
	{
		error_echo(user_name);
		return (-1);
	}
	else
	{
		if (S_ISDIR(s.st_mode))
			ft_putstr(buffer);
		else
		{
			error_echo(user_name);
			return (-1);
		}
	}
	return (0);
}

int		handle_tilde(t_hustru *big_struc, char *command, int i)
{
	char	*str;
	char	buff[4096];
	char	user_name[33];
	int		e;
	int		j;

	ft_bzero(buff, 4096);
	ft_bzero(user_name, 33);
	e = 0;
	if (command[i + 1] != ' ' && command[i + 1])
	{
		str = find_in_env(big_struc->lkd_env, ft_strdup("HOME"));
		while (command[i + e] && command[i + e] != ' '
		&& command[i + e] != '\t')
			e++;
		ft_strnncpy(user_name, command, i + 1, i + e);
		j = ft_strlen(str);
		while (str[j] != '/')
			j--;
		ft_strncpy(buff, str, j + 1);
		if (verify_folder(buff, user_name, str) == -1)
		{
			big_struc->last_ret = 1;
			return (-1);
		}
		big_struc->last_ret = 0;
		return (i + e + 1);
	}
	else
		return (handle_tilde2(big_struc->lkd_env, i));
}

int		return_i(char *command)
{
	int i;

	i = 0;
	while (command[i] == ' ' || command[i] == '\t')
		i++;
	while (command[i] && ft_isalnum(command[i]))
		i++;
	return (++i);
}

int		echo(t_hustru *big_struc, char *command)
{
	int e;
	int i;

	e = 0;
	i = return_i(command);
	if (ft_strstr(command, "-n") != NULL)
	{
		e = 1;
		i += 3;
	}
	while (command[i - 1])
	{
		if (command[i] == '\t' || (command[i] == ' '
		&& (command[i + 1] == ' ' || command[i - 1] == ' ')))
			i++;
		else if (command[i] == '$')
			i = handle_dollar(big_struc, command, i);
		else if (command[i] == '~')
		{
			if ((i = handle_tilde(big_struc, command, i)) == -1)
				return (big_struc->last_ret);
		}
		else
			ft_putchar(command[i++]);
	}
	if (e == 0)
		ft_putchar('\n');
	return (0);
}
