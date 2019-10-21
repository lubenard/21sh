/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/21 18:19:17 by lubenard          #+#    #+#             */
/*   Updated: 2019/10/21 18:21:03 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh21.h>

int		is_between_quotes(char *command, int quote_mode)
{
	if (command[0] != '\''
	&& command[ft_strlen(command) - 1] != '\''
	&& quote_mode == 1)
		return (0);
	else if (command[0] != '\"'
	&& command[ft_strlen(command) - 1] != '\"'
	&& quote_mode == 2)
		return (0);
	else if (command[0] != '\''
	&& command[ft_strlen(command) - 1] != '\''
	&& command[0] != '\"'
	&& command[ft_strlen(command) - 1] != '\"'
	&& quote_mode == 3)
		return (0);
	return (1);
}

int		is_between_quotes2(char **command, char quote_char)
{
	int i;

	i = 0;
	while (command[i])
	{
		if (ft_strchr(command[i], quote_char) && !ft_strchr(command[i], '\'')
		&& !ft_strchr(command[i], '\"'))
			return (0);
		else if (ft_strchr(command[i], quote_char)
		&& (ft_strchr(command[i], '\'')
		|| ft_strchr(command[i], '\"')))
			return (1);
		i++;
	}
	return (0);
}

void	remove_quote_bis(char **command, int i, int e)
{
	char *tmp;

	if (ft_strchr(*command, '\'') || ft_strchr(*command, '\"'))
	{
		while ((*command)[i])
		{
			if ((*command)[i] != '\'' && (*command)[i] != '\"')
				e++;
			i++;
		}
		if (!(tmp = ft_strnew(e)))
			return ;
		e = 0;
		i = 0;
		while ((*command)[i])
		{
			if ((*command)[i] != '\'' && (*command)[i] != '\"')
				tmp[e++] = (*command)[i];
			i++;
		}
		free((*command));
		(*command) = tmp;
	}
}

void	remove_quote(char ***command)
{
	int		i;
	int		e;
	int		j;

	j = 0;
	while ((*command)[j])
	{
		i = 0;
		e = 0;
		remove_quote_bis(&((*command)[j]), i, e);
		j++;
	}
}

/*
** Replace the ~ or the $ with his equivalence
*/

void	swap_elem(char **command, char *replace)
{
	free(*command);
	*command = replace;
}
