/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/15 11:59:46 by lubenard          #+#    #+#             */
/*   Updated: 2019/10/15 23:23:42 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh21.h>

char	*handle_dollar(t_hustru *big_struc, char *command)
{
	int		e;
	int		i;
	int		a;
	int		occur;

	(void)big_struc;
	a = 0;
	occur = ft_occur(command, '$');
	printf("%d\n", occur);
	while (a < occur)
	{
		printf("Je boucle, a vaut %d\n", a);
		i = ft_strchri(command, '$');
		e = 0;
		if (command[i])
		{
			if (command[i + 1] == '?')
				return (ft_itoa(big_struc->last_ret));
			while (command[i + e] && ft_isalnum(command[i + e]))
				e++;
			return (find_in_env(big_struc->lkd_env, ft_strsub(command, i, e)));
		}
		printf("|%c|\n", command[e]);
		while (command[i] && command[i] != '$')
			i++;
		i++;
		a++;
		printf("A = %d\n", a);
	}
	return ("");
}

char	*verify_folder(char buffer[4096], char user_name[4096], char *str)
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
	ft_strcat(buffer, user_name);
	free(str);
	free(str2);
	err = stat(buffer, &s);
	if (err == -1 || !S_ISDIR(s.st_mode))
		return (ft_strjoin("~", user_name));
	return (ft_strdup(buffer));
}

char	*handle_tilde(t_hustru *big_struc, char *command)
{
	char	*str;
	char	*tmp;
	char	buff[4096];
	char	user_name[4096];
	int		i;

	ft_bzero(buff, 4096);
	ft_bzero(user_name, 4096);
	i = ft_strchri(command, '~');
	str = find_in_env(big_struc->lkd_env, ft_strdup("HOME"));
	if (command[i + 1] && ft_strlen(command) > 1)
	{
		if (command[i] == '/')
		{
			ft_strcpy(buff, "/");
			ft_stricat(buff, command, i + 1);
			tmp = ft_strjoin(str, buff);
			free(str);
			return (tmp);
		}
		handle_tilde2(user_name, command, i);
		return (verify_folder(buff, user_name, str));
	}
	else
		return (str);
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
