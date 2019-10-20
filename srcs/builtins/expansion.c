/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <lubenard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/20 21:02:47 by lubenard          #+#    #+#             */
/*   Updated: 2019/10/20 21:13:03 by lubenard         ###   ########.fr       */
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

/*
** Replace dollar with good env variable
*/

char	*handle_dollar(t_hustru *big_struc, char *command)
{
	int		e;
	int		i;
	int		a;
	char	*ret;
	char	*tmp;

	a = 0;
	ret = NULL;
	i = ft_strchri(command, '$');
	while (a < ft_occur(command, '$'))
	{
		e = 0;
		if (!ret)
		{
		//	printf("Je malloc de %d\n", handle_dollar3(big_struc, command, i, e));
			ret = ft_strnew(handle_dollar3(big_struc, command, i, e));
		}
		else
		{
		//	printf("Je realloc de + %d\n", handle_dollar3(big_struc, command, i, e));
			ft_realloc(&ret, handle_dollar3(big_struc, command, i, e));
		}
		tmp = handle_dollar2(big_struc, command, &i, &e);
		ft_strcat(ret, tmp);
		free(tmp);
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
