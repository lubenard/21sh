/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/23 17:28:53 by lubenard          #+#    #+#             */
/*   Updated: 2019/09/23 19:30:50 by lubenard         ###   ########.fr       */
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
	tmp = malloc(sizeof(char*) * (nb + 1));
	while (str[i] != '\0')
	{
		//ft_putchar(str[i]);
		if (str[i] != ' ')
		{
			if (ft_isdigit(str[i]))
			{
				mark = char_number((str + i), ' ', '<', '>');
				tmp[x] = malloc(sizeof(char) * mark + 1);
				mark += i;
				while (str[i] && i < mark)
					tmp[x][y++] = str[i++];
				tmp[x][y] = '\0';
				x++;
				y = 0;
			}
			else if (str[i] == '<' || str[i] == '>')
			{
				mark = char_number((str + i), ' ', '<', '>');
				//ft_putnbr(mark);
				//ft_putchar('-');
				//ft_putnbr(i);
				//ft_putchar('-');
				tmp[x] = malloc(sizeof(char) * mark + 1);
				mark += i;
				//ft_putnbr(mark);
				//ft_putchar(' ');
				while (str[i] && i < mark)
					tmp[x][y++] = str[i++];
				tmp[x][y] = '\0';
				x++;
				y = 0;
			}
			else
			{
				mark = char_number((str + i), ' ', '<', '>');
				//ft_putnbr(mark);
				//ft_putchar('-');
				//ft_putnbr(i);
				//ft_putchar('-');
				tmp[x] = malloc(sizeof(char) * mark + 1);
				mark += i;
				//ft_putnbr(mark);
				//ft_putchar(' ');
				while (str[i] && i < mark)
					tmp[x][y++] = str[i++];
				tmp[x][y] = '\0';
				x++;
				y = 0;
			}
			i--;
		}
		i++;
	}
	tmp[x] = NULL;
	x = 0;
	//ft_putchar('\n');
	while (tmp[x] != NULL)
		ft_putendl(tmp[x++]);
	return (0);
}
