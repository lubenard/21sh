/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/21 18:19:17 by lubenard          #+#    #+#             */
/*   Updated: 2019/12/16 23:33:12 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh21.h>
#include <input.h>

/*
** Return if between simple or double quote, or one of them
*/

int		is_between_quotes(char *command, int quote_mode)
{
	if (!command || !ft_strcmp(command, ""))
		return (0);
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

void	remove_quote_bis(char **command)
{
	char	*dst;
	char	c;
	int		i;
	int		j;

	j = 0;
	i = 0;
	if (!(dst = ft_strnew(ft_strlen(*command))))
		return ;
	while ((*command)[i])
	{
		if ((*command)[i] == '\'' || (*command)[i] == '\"')
		{
			c = (*command)[i++];
			while ((*command)[i] && (*command)[i] != c)
				dst[j++] = (*command)[i++];
		}
		else
			dst[j++] = (*command)[i];
		i++;
	}
	free(*command);
	(*command) = dst;
}

/*
** Will delete quote if needed
*/


void	remove_quote(char ***command)
{
	int		j;

	j = 0;
	while ((*command)[j])
	{
		if (is_between_quotes((*command)[j], 3))
			remove_quote_bis(&((*command)[j]));
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
