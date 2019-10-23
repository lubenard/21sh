/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tilde_expansion.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/23 12:49:28 by lubenard          #+#    #+#             */
/*   Updated: 2019/10/23 12:50:00 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh21.h>

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
