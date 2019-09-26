/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/25 15:10:40 by lubenard          #+#    #+#             */
/*   Updated: 2019/09/26 19:26:55 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh21.h>

int		char_number(char *str, char c, char d, char e)
{
	int		i;

	i = 0;
	if  (str[i] && (str[i] == d || str[i] == e))
	{
		if (str[i + 1] == '&')
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
	else if  (str[i] && str[i] != c && str[i] != d && str[i] != e)
	{
		if (ft_isdigit(str[i]) && str[i + 1] && str[i + 1] == '>')
		{
			c = '>';
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
	return (0);
}

char	**parse_redir(char *str)
{
	int		i;
	int		mark;
	int		x;
	char	**tmp;

	i = 0;
	mark = 0;
	x = 0;
	if (!(tmp = malloc(sizeof(char*) * (1000 + 1))))
		return (NULL);
	while (str[i])
	{
		if (str[i] != ' ')
		{
			mark = char_number((str + i), ' ', '<', '>');
			if (!(tmp[x] = ft_strnew(mark)))
				return (NULL);
			mark += i;
			ft_strnncpy(tmp[x], str, i, mark);
			i += ft_strlen(tmp[x]);
			x++;
			i--;
		}
		i++;
	}
	tmp[x] = NULL;
	return (tmp);
}
