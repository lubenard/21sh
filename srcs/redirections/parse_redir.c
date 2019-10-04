/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/25 15:10:40 by lubenard          #+#    #+#             */
/*   Updated: 2019/10/04 17:33:29 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh21.h>

int		char_numberbis(char *str, char c, char d, char e)
{
	int i;

	i = 0;
	if (ft_isdigit(str[i]) && str[i + 1] && (str[i + 1] == '>' || str[i + 1] == '<'))
	{
		c = str[i + 1];
		if (str[i + 2] && str[i + 2] == '&')
			c = ' ';
		while (str[i] && str[i] != c)
			i++;
		i++;
	}
	else
	{
		while (str[i] && str[i] != c && str[i] != d && str[i] != e)
			i++;
	}
	return (i);
}

int		char_number(char *str, char c, char d, char e)
{
	int		i;

	i = 0;
	if (str[i] && (str[i] == d || str[i] == e || str[i] == '&'))
	{
		if (str[i] == '&' || str[i + 1] == '&')
		{
			while (str[i] && str[i] != ' ')
				i++;
		}
		else
		{
			while (str[i] && (str[i] == d || str[i] == e))
				i++;
		}
		return (i);
	}
	else if (str[i] && str[i] != c && str[i] != d && str[i] != e)
		return (char_numberbis(str, c, d, e));
	return (i);
}

char	**parse_redir(char *str)
{
	int		i;
	int		mark;
	int		x;
	char	**tmp;

	i = -1;
	mark = 0;
	x = 0;
	if (!(tmp = malloc(sizeof(char *) * (1000 + 1))))
		return (NULL);
	while (str[++i])
	{
		if (str[i] != ' ')
		{
			mark = char_number((str + i), ' ', '<', '>');
			if (!(tmp[x] = ft_strnew(mark)))
				return (NULL);
			mark += i;
			ft_strnncpy(tmp[x], str, i, mark);
			i += ft_strlen(tmp[x]) - 1;
			x++;
		}
	}
	tmp[x] = NULL;
	return (tmp);
}
