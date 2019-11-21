/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tilde_expansion.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/23 12:49:28 by lubenard          #+#    #+#             */
/*   Updated: 2019/11/21 14:20:23 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh21.h>

/*
** Compact command for pipes, because pipe only accept
** char * and not char **
*/

char	*recompact_command_expansion(char **tab)
{
	int		i;
	int		e;
	char	*ret;

	i = 0;
	e = 0;
	while (tab[e])
		i += ft_strlen(tab[e++]);
	if (!(ret = ft_strnew(i)))
		return (NULL);
	e = 0;
	while (tab[e])
	{
		ft_strcat(ret, tab[e]);
		ft_strdel(&tab[e]);
		e++;
	}
	ft_deltab(&tab);
	return (ret);
}

/*
** Check if folder exist for ~/username
*/

char	*verify_folder(char *user_name)
{
	struct stat		s;
	int				err;
	char			*buffer;

	buffer = ft_strjoin("/Users/", user_name);
	err = stat(buffer, &s);
	ft_strdel(&buffer);
	if (err == -1 || !S_ISDIR(s.st_mode))
		return (ft_strjoin("~", user_name));
	return (ft_strjoin("/Users/", user_name));
}

void	replace_tilde(t_hustru *big_struc, char ***tilde)
{
	int		i;
	int		already_replaced;

	i = 0;
	already_replaced = 0;
	while ((*tilde)[i])
	{
		if (i != 0 && !ft_strcmp((*tilde)[i - 1], "$"))
		{
			i++;
			continue;
		}
		if ((*tilde)[i + 1] && (*tilde)[i + 1][0] == '$')
		{
			i++;
			continue ;
		}
		if ((*tilde)[i] && !already_replaced && (*tilde)[i + 1]
		&& !ft_strcmp((*tilde)[i], "~") && ft_isalnum((*tilde)[i + 1][0]))
		{
			free((*tilde)[i]);
			(*tilde)[i] = verify_folder((*tilde)[i + 1]);
			free((*tilde)[i + 1]);
			(*tilde)[i + 1] = ft_strdup("");
			already_replaced = 1;
		}
		else if ((*tilde)[i] && !already_replaced && !ft_strcmp((*tilde)[i], "~"))
		{
			if (ft_strcmp((*tilde)[i + 1], "~"))
			{
				free((*tilde)[i]);
				(*tilde)[i] = ft_strdup(big_struc->home_env_var);
			}
			if ((*tilde)[i + 1] && (*tilde)[i + 1][0] != ':')
				already_replaced = 1;
		}
		i++;
	}
}

/*
** Handle ~ and replace it if needded
*/

char	*handle_tilde(t_hustru *big_struc, char *command)
{
	char	**ret;

	ret = ft_strksplit(command, '~');
	replace_tilde(big_struc, &ret);
	return (recompact_command_expansion(ret));
}
