/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/15 11:59:46 by lubenard          #+#    #+#             */
/*   Updated: 2019/08/28 10:42:10 by lubenard         ###   ########.fr       */
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
	if (command[1])
	{
		if (command[i + 1] == '?')
		{
			ft_putnbr(big_struc->last_ret);
			return (0);
		}
		while (command[e] && ft_isalnum(command[e]))
			e++;
		str = find_in_env(big_struc->lkd_env, ft_strsub(command, i, e));
		ft_putstr(str);
		free(str);
	}
	return (0);
}

int		verify_folder(char buffer[4096], char user_name[4096], char *str)
{
	struct stat		s;
	int				err;
	char			*str2;
	int				j;

	j = ft_strlen(str);
	while (str[j - 1] != '/')
		j--;
	str2 = ft_strsub(str, 0, j);
	ft_strcpy(buffer, str2);
	ft_stricpy(buffer, user_name, 1);
	err = stat(buffer, &s);
	free(str);
	free(str2);
	if (err == -1)
		return (error_echo(user_name));
	else
	{
		if (S_ISDIR(s.st_mode))
			ft_putstr(buffer);
		else
			return (error_echo(user_name));
	}
	return (0);
}

int		handle_tilde(t_hustru *big_struc, char *command)
{
	char	*str;
	char	buff[4096];
	char	user_name[4096];

	ft_bzero(buff, 4096);
	ft_bzero(user_name, 4096);
	if (command[1] && (ft_isalpha(command[1]) || command[1] == '/'))
	{
		str = find_in_env(big_struc->lkd_env, ft_strdup("HOME"));
		ft_strcpy(user_name, command);
		if (command[1] == '/')
		{
			ft_stricpy(buff, command, 1);
			handle_tilde2(big_struc->lkd_env);
			ft_putendl(buff);
			free(str);
			return (0);
		}
		if (verify_folder(buff, user_name, str) == -1)
			return (big_struc->last_ret = 1);
		handle_tilde2(big_struc->lkd_env);
		return (big_struc->last_ret = 0);
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
