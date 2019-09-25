/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/25 01:21:20 by lubenard          #+#    #+#             */
/*   Updated: 2019/09/25 01:46:09 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh21.h>

int		char_number(char *str, char c, char d, char e)
{
	int		i;

	i = 0;
	if (str[i] && (str[i] == d || str[i] == e))
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
	else if (str[i] != '\0' && str[i] != c && str[i] != d && str[i] != e)
	{
		while (str[i] != '\0' && str[i] != c && str[i] != d && str[i] != e)
			i++;
		return (i);
	}
	return (0);
}

int		parse_redir(char *str)
{
	int		i;
	int		mark;
	int		x;
	int		y;
	char	**tmp;
	int		nb;

	i = 0;
	mark = 0;
	x = 0;
	y = 0;
	nb = ft_occur(str, '<') + ft_occur(str, '>') + ft_occur(str, ' ');
	if (!(tmp = malloc(sizeof(char*) * (nb + 1))))
		return (1);
	while (str[i] != '\0')
	{
		if (str[i] != ' ')
		{
			if (ft_isdigit(str[i]))
			{
				mark = char_number((str + i), ' ', '<', '>');
				if (!(tmp[x] = malloc(sizeof(char) * mark + 1)))
					return (1);
				mark += i;
				ft_strnncpy(tmp[x], str, i, mark);
				i += ft_strlen(tmp[x]);
				x++;
			}
			else if (str[i] == '<' || str[i] == '>')
			{
				mark = char_number((str + i), ' ', '<', '>');
				if (!(tmp[x] = malloc(sizeof(char) * mark + 1)))
					return (1);
				mark += i;
				ft_strnncpy(tmp[x], str, i, mark);
				i += ft_strlen(tmp[x]);
				x++;
			}
			else
			{
				mark = char_number((str + i), ' ', '<', '>');
				if (!(tmp[x] = malloc(sizeof(char) * mark + 1)))
					return (1);
				mark += i;
				ft_strnncpy(tmp[x], str, i, mark);
				i += ft_strlen(tmp[x]);
				x++;
			}
			i--;
		}
		i++;
	}
	tmp[x] = NULL;
	x = 0;
	while (tmp[x] != NULL)
		ft_putendl(tmp[x++]);
	return (0);
}
