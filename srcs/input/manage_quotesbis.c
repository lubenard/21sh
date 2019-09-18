/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_quotesbis.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymarcill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/17 21:06:58 by ymarcill          #+#    #+#             */
/*   Updated: 2019/09/18 17:24:40 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <input.h>

int		is_there(char *line, int i, char *c, int *quotes)
{
	*c = line[i];
	*quotes = 1;
	while (line[i++])
	{
		if (line[i] == *c)
		{
			*quotes = 0;
			break ;
		}
	}
	return (i);
}

int		is_it(int *quotes, char **tmp, char c, char i)
{
	if (i == c)
	{
		*quotes += 1;
		*tmp = "yes";
		return (1);
	}
	return (0);
}

char	*do_i_have_to_do_it_quote(char *line, int *i, t_hustru *big_struc,
		char **tmp)
{
	int		quotes;
	char	c;

	*i = is_there(line, *i, &c, &quotes);
	if (quotes % 2 != 0)
	{
		ft_putstr_fd("\r> ", 0);
		line = ft_strjoinnf(line, "\n");
		while ((line = get_inline(line, big_struc)))
		{
			while (line[*i])
			{
				if (is_it(&quotes, tmp, c, line[*i]))
					break ;
				*i += 1;
			}
			if (quotes % 2 == 0 || line[ft_strlenu(line) - 1] == 7)
			{
				ft_putchar_fd('\n', 0);
				break ;
			}
			ft_putstr_fd("\n\r> ", 0);
		}
	}
	return (line);
}

char	*suppr_lastchar(char *line)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	j = 0;
	if ((tmp = malloc(sizeof(char) * (ft_strlenu(line) + 1))) == NULL)
		return (line);
	while (i < ft_strlenu(line) - 1)
		tmp[j++] = line[i++];
	tmp[j] = '\0';
	free(line);
	line = ft_strdup(tmp);
	free(g_mainline);
	g_mainline = NULL;
	return (line);
}
