/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/15 11:59:46 by lubenard          #+#    #+#             */
/*   Updated: 2019/09/13 22:57:09 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh21.h>

char	*handle_dollar(t_hustru *big_struc, char *command)
{
	int		e;
	int		i;

	i = 0;
	e = 0;
	if (command[1])
	{
		if (command[i + 1] == '?')
			return (ft_itoa(big_struc->last_ret));
		while (command[e] && ft_isalnum(command[e]))
			e++;
		return (find_in_env(big_struc->lkd_env, ft_strsub(command, i, e)));
	}
	return (NULL);
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
	if (err == -1 || S_ISDIR(s.st_mode))
		return (ft_strjoin("~", user_name));
	return (ft_strdup(buffer));
}

char	*handle_tilde(t_hustru *big_struc, char *command)
{
	char	*str;
	char	*tmp;
	char	buff[4096];
	char	user_name[4096];

	ft_bzero(buff, 4096);
	ft_bzero(user_name, 4096);
	if (command[1] && (ft_isalpha(command[1]) || command[1] == '/'))
	{
		str = find_in_env(big_struc->lkd_env, ft_strdup("HOME"));
		if (command[1] == '/')
		{
			ft_stricpy(buff, command, 1);
			tmp = ft_strjoin(str, buff);
			free(str);
			return (tmp);
		}
		ft_stricpy(user_name, command, 1);
		if ((tmp = verify_folder(buff, user_name, str)) == NULL) 
		{
			// TODO modify to make struct returning 1 in echo
			big_struc->last_ret = 1;
			return (tmp);
		}
	}
	else
		return(find_in_env(big_struc->lkd_env, ft_strdup("HOME")));
	return (tmp);
}

int		ft_echo(t_hustru *big_struc, char **command)
{
	int		e;
	int		i;

	(void)big_struc;
	i = 1;
	e = (!ft_strcmp(command[1], "-n")) ? 1 : 0;
	while (command[i + e])
	{
		if (command[i + e])
			ft_putstr(command[i + e]);
		i++;
		ft_putchar(' ');
	}
	if (e == 0)
		ft_putchar('\n');
	return (0);
}
