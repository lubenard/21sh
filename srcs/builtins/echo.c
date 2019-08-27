/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/15 11:59:46 by lubenard          #+#    #+#             */
/*   Updated: 2019/08/27 18:50:03 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh21.h>

int		handle_dollar(t_hustru *big_struc, char *command)
{
	int		e;
	char	*str;
	int		i;

	i = 0;
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

int		handle_tilde(t_hustru *big_struc, char *command)
{
	char	*str;
	char	buff[4096];
	char	user_name[33];
	int		j;

	ft_bzero(buff, 4096);
	ft_bzero(user_name, 33);
	if (command[1] && (ft_isalpha(command[1]) || command[1] == '/'))
	{
		str = find_in_env(big_struc->lkd_env, ft_strdup("HOME"));
		printf("je parse %s\n", command);
		ft_strcpy(user_name, command);
		j = ft_strlen(command);
		while (command[j] != '/')
			j--;
		ft_strnncpy(buff, command, j + 1, ft_strlen(command)); //Faire une fonction qui copie depuis n char jusqu'a la fin
		if (command[1] == '/')
		{
			handle_tilde2(big_struc->lkd_env);
			ft_putstr("/"); //Faire une fonction qui permet d'afficher une chaine puis une variable et inversion
			ft_putendl(buff);
			return (0);
		}
		if (verify_folder(buff, user_name, str) == -1)
		{
			big_struc->last_ret = 1;
			return (-1);
		}
		big_struc->last_ret = 0;
		return (0);
	}
	else
		return (handle_tilde2(big_struc->lkd_env));
}

int		ft_echo(t_hustru *big_struc, char **command)
{
	int e;
	int i;

	e = 0;
	i = 1;
	if (!ft_strcmp(command[1], "-n"))
		e = 1;
	while (command[i + e])
	{
		if (command[i + e][0] == '$')
			handle_dollar(big_struc, command[i + e]);
		else if (command[i + e][0] == '~')
		{
			if (handle_tilde(big_struc, command[i + e]) == -1)
				return (big_struc->last_ret);
		}
		else
			ft_putstr(command[i + e]);
		i++;
	}
	if (e == 0)
		ft_putchar('\n');
	return (0);
}
