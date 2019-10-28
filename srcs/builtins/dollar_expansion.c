/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_expansion.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <lubenard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/20 21:02:47 by lubenard          #+#    #+#             */
/*   Updated: 2019/10/28 16:04:56 by lubenard         ###   ########.fr       */
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
		if (command[*i] == '?')
			return (ft_itoa(big_struc->last_ret));
		while (command[*i + *e] && ft_isalnum(command[*i + *e]))
			(*e)++;
		return (find_in_env(big_struc->lkd_env, ft_strsub(command, *i, *e)));
	}
	return (NULL);
}

/*
** Join if needed to avoid bug in setenv
*/

char	*handle_ret_dollar(char *command, char *ret)
{
	int		i;
	char	*str;
	char	*tmp2;

	i = ft_strchri(command, '$');
	if (i != 0)
	{
		tmp2 = extract_first(command, '$');
		str = ft_strjoin(tmp2, ret);
		free(ret);
		free(tmp2);
		return (str);
	}
	return (ret);
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
			ret = ft_strnew(handle_dollar3(big_struc, command, i, e));
		else
			ft_realloc(&ret, handle_dollar3(big_struc, command, i, e));
		tmp = handle_dollar2(big_struc, command, &i, &e);
		ft_strcat(ret, tmp);
		free(tmp);
		while (command[i] && command[i] != '$')
			i++;
		i++;
		a++;
	}
	return (handle_ret_dollar(command, ret));
}
