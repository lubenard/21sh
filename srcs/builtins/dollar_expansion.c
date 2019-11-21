/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_expansion.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <lubenard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/20 21:02:47 by lubenard          #+#    #+#             */
/*   Updated: 2019/11/21 14:45:59 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh21.h>

void	handle_dollar_value(char ***dollar, int i)
{
	char	*value;
	int		j;

	j = 0;
	if ((*dollar)[i + 1])
	{
		while (ft_isalnum((*dollar)[i + 1][j]))
			j++;
		value = ft_strsub((*dollar)[i + 1], j, ft_strlen((*dollar)[i + 1]) - j);
		ft_strdel(&((*dollar)[i + 1]));
		(*dollar)[i + 1] = value;
	}
}

int		handle_special_expansions(t_hustru *big_struc, char ***dollar, int *i)
{
	char	*value;

	if ((*dollar)[*i + 1][0] == '?')
	{
		value = ft_strsub((*dollar)[*i + 1], 1,
		ft_strlen((*dollar)[*i + 1]) - 1);
		free((*dollar)[*i]);
		free((*dollar)[*i + 1]);
		(*dollar)[*i] = ft_itoa(big_struc->last_ret);
		(*dollar)[*i + 1] = value;
		(*i)++;
		return (1);
	}
	return (0);
}

void	replace_dollar(t_hustru *big_struc, char ***dollar)
{
	int		i;
	int		j;
	char	*to_search;
	char	*value;

	i = 0;
	while ((*dollar)[i])
	{
		if ((*dollar)[i] && (*dollar)[i + 1] && !ft_strcmp((*dollar)[i], "$"))
		{
			if (handle_special_expansions(big_struc, dollar, &i))
				continue;
			j = 0;
			while (ft_isalnum((*dollar)[i + 1][j]))
				j++;
			to_search = ft_strsub((*dollar)[i + 1], 0, j);
			free((*dollar)[i]);
			value = find_in_env(big_struc->lkd_env, to_search);
			(*dollar)[i] = (value) ? value : ft_strdup("");
			handle_dollar_value(dollar, i);
		}
		i++;
	}
}

char	*handle_dollar(t_hustru *big_struc, char *command)
{
	char **ret;

	ret = ft_strksplit(command, '$');
	replace_dollar(big_struc, &ret);
	return (recompact_command_expansion(ret));
}
