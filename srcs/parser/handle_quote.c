/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/21 18:19:17 by lubenard          #+#    #+#             */
/*   Updated: 2019/11/19 02:16:09 by ymarcill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh21.h>
#include <input.h>

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

void	remove_quote_bis(char **command, int i, int e, char to_delete)
{
	char *tmp;

	while ((*command)[i])
	{
		if ((*command)[i] != to_delete)
			e++;
		i++;
	}
	if (!(tmp = ft_strnew(e)))
		return ;
	e = 0;
	i = 0;
	while ((*command)[i])
	{
		if ((*command)[i] != to_delete)
			tmp[e++] = (*command)[i];
		i++;
	}
	free(*command);
	(*command) = tmp;
}

void	remove_quote(char ***command)
{
/*	int		i;
	int		j;
	char	c;
	char	*tmp;

	i = 0;
	j = 0;
	if (!(tmp = malloc(sizeof(char) * (ft_strlen(command) + 1))))
		return (NULL);
	while (command[i])
	{
		if (command[i] == '\'' || command[i] == '\"')
		{
			c = command[i++];
			while (command[i] && command[i] != c)
				tmp[j++] = command[i++];
		}
		else
			tmp[j++] = command[i++];
	}
	tmp[j] = '\0';
	//ft_strdel(&command);
	return (tmp);*/
	int		i;
	int		e;
	int		j;

	j = 0;
	while ((*command)[j])
	{
		i = 0;
		e = 0;
		if (is_between_quotes((*command)[j], 1))
			remove_quote_bis(&((*command)[j]), i, e, '\'');
		else if (is_between_quotes((*command)[j], 2))
			remove_quote_bis(&((*command)[j]), i, e, '\"');
		j++;
	}
}

/*char	**remove_quote(char **command)
{
	int		i;
	int		j;
	char	**tmp;

	i = 0;
	j = 0;
	if (!(tmp = malloc(sizeof(char*) * (ft_tablen(command) + 1))))
		return (NULL);
	ft_putnbr(ft_tablen(command));
	while (command[i])
		tmp[j++] = remove_quote_one(command[i++]);
	tmp[j] = NULL;
	//free(command);
	command = NULL;
	return (tmp);
}*/

/*
** Replace the ~ or the $ with his equivalence
*/

void	swap_elem(char **command, char *replace)
{
	free(*command);
	*command = replace;
}
