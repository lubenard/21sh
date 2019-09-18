/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insert_del.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymarcill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/20 17:13:06 by ymarcill          #+#    #+#             */
/*   Updated: 2019/09/18 17:24:36 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <input.h>

int		*reprint_line(int *mainindex, char *str, int **pos, int *prompt)
{
	int	i;
	int	*coord;

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
		{
			coord[1] = 0;
			str[i] != '\n' ? ft_putstr_fd("\e[E", 0) : 0;
		}
		*mainindex += 1;
		i++;
	}
	free(coord);
	return (pos[0]);
}

void	delete_c(int **pos, int *prompt, int *mainindex, int w)
{
	int				i;
	int				j;
	char			*str;

	i = 0;
	j = 0;
	str = NULL;
	if (*mainindex != 0)
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
			left_arrow(mainindex, prompt, pos[0]);
		free(g_mainline);
		g_mainline = ft_strdup(str);
		free(str);
	}
}
