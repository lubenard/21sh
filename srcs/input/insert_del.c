/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insert_del.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymarcill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/20 17:13:06 by ymarcill          #+#    #+#             */
/*   Updated: 2019/09/24 21:10:59 by ymarcill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <input.h>

int		if_last_co(char c)
{
	if (c != '\n')
		ft_putstr_fd("\e[E", 0);
	return (0);
}

char	*del_char(int *w, int mainindex, int *i, int *j)
{
	char    *str;

	str = ft_strnew(ft_strlenu(g_mainline));
	if (*w == -1 && mainindex - *w == ft_strlenu(g_mainline))
		*w = 0;
	while (g_mainline[*i] != '\0')
	{
		if (*i != mainindex - *w)
		{
			str[*j] = g_mainline[*i];
			*j += 1;
		}
		*i += 1;
	}
	str[*i] = '\0';
	return (str);
}


int		*reprint_line(int *mainindex, char *str, int **pos, int *prompt)
{
	int i;
	int *coord;

	i = 0;
	free(pos[0]);
	pos[0] = malloc(sizeof(int) * (ft_strlen(str)));
	coord = malloc(sizeof(int) * 2);
	coord[0] = prompt[0];
	coord[1] = prompt[1] - 1;
	while (str[i])
	{
		coord[1]++;
		if (i > 0 && str[i - 1] == '\n')
			coord[1] = 1;
		ft_putchar_fd(str[i], 0);
		pos[0][i] = coord[1];
		if (coord[1] == w.ws_col)
			coord[1] = if_last_co(str[i]);
		*mainindex += 1;
		i++;
	}
	free(coord);
	return (pos[0]);
}

void	delete_c(int **pos, int *prompt, int *mainindex, int w)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	j = 0;
	str = NULL;
	if (*mainindex != 0 || (*mainindex == 0 && w== -1))
	{
		str = ft_strnew(ft_strlenu(g_mainline));
		w = w == -1 && *mainindex - w == ft_strlenu(g_mainline) ? 0 : w;
		while (g_mainline[i])
		{
			if (i != *mainindex - w)
				str[j++] = g_mainline[i];
			i++;
		}
		str[j] = '\0';
		j = *mainindex;
		clean(prompt, mainindex, pos[0]);
		pos[0] = reprint_line(mainindex, str, pos, prompt);
		j = w == 1 ? j + 1 : j + 2;
		while (i-- >= j)
			left_arrow(mainindex, pos[0]);
		free(g_mainline);
		g_mainline = ft_strdup(str);
		free(str);
	}
}
