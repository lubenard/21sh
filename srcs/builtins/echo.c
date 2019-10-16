/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/15 11:59:46 by lubenard          #+#    #+#             */
/*   Updated: 2019/10/16 14:36:13 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh21.h>

int		handle_dollar3(t_hustru *big_struc, char *command, int i, int e)
{
	char	*tmp;
	int		len;

	if (command[i])
	{
		if (command[i + 1] == '?')
			return (1);
		while (command[i + e] && ft_isalnum(command[i + e]))
			e++;
		tmp = find_in_env(big_struc->lkd_env, ft_strsub(command, i, e));
		len = ft_strlen(tmp);
		free(tmp);
		return (len);
	}
	return (0);
}

char	*handle_dollar2(t_hustru *big_struc, char *command, int *i, int *e)
{
	if (command[*i])
	{
		if (command[*i + 1] == '?')
			return (ft_itoa(big_struc->last_ret));
		while (command[*i + *e] && ft_isalnum(command[*i + *e]))
			(*e)++;
		return (find_in_env(big_struc->lkd_env, ft_strsub(command, *i, *e)));
	}
	return (NULL);
}

char	*handle_dollar(t_hustru *big_struc, char *command)
{
	int		e;
	int		i;
	int		a;
	int		occur;
	char	*ret;

	a = 0;
	ret = NULL;
	occur = ft_occur(command, '$');
	i = ft_strchri(command, '$');
	while (a < occur)
	{
		e = 0;
		if (ret == NULL)
		{
			printf("Je malloc de %d\n", handle_dollar3(big_struc, command, i, e));
			ret = ft_strnew(handle_dollar3(big_struc, command, i, e));
		}
		else
		{
			printf("Je realloc de + %d\n", handle_dollar3(big_struc, command, i, e));
			ft_realloc(&ret, handle_dollar3(big_struc, command, i, e));
		}
		ft_strcat(ret, handle_dollar2(big_struc, command, &i, &e));
		while (command[i] && command[i] != '$')
			i++;
		i++;
		a++;
	}
	return (ret);
}

/*
** Check if folder exist for ~/
*/

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

/*
** Handle ~ and replace it if needded
*/

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
