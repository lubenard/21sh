/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_copy_cut_paste_del.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymarcill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/17 19:24:31 by ymarcill          #+#    #+#             */
/*   Updated: 2019/10/04 15:27:01 by ymarcill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <input.h>

void	paste_no_insert(char *str, int *mainindex, int **prompt)
{
	int		i;
	int		*coord;
	char	*tmp;

	i = 0;
	while (str[i])
	{
		coord = get_coord(get_cursor_position());
		ft_putchar_fd(str[i], 0);
		*mainindex += 1;
		last_line_col(coord, prompt, str[i]);
		free(coord);
		i++;
	}
	tmp = ft_strdup(g_mainline);
	free(g_mainline);
	g_mainline = ft_strjoinnf(tmp, str);
	free(tmp);
}

void	paste_insert(int *mainindex, char *str, int **pos, int **prompt)
{
	t_coord	c;

	c.i = 0;
	c.j = 0;
	c.k = 0;
	if (!(c.tmp = malloc(sizeof(char) * (ft_strlenu(g_mainline)
		+ ft_strlenu(str) + 2))))
		return ;
	while (g_mainline[c.i])
	{
		if (c.i == *mainindex)
		{
			while (str[c.k])
				c.tmp[c.j++] = str[c.k++];
		}
		c.tmp[c.j++] = g_mainline[c.i++];
	}
	c.tmp[c.j] = '\0';
	c.k = *mainindex;
	clean(prompt[0], mainindex, pos[0]);
	pos[0] = ft_print_line(c.tmp, pos, mainindex, prompt);
	g_mainline = ft_strdup(c.tmp);
	while (c.j-- > c.k + ft_strlenu(str))
		left_arrow(mainindex, NULL);
	free(c.tmp);
}

void	paste(char *str, int **prompt, int *mainindex, int **pos)
{
	if (*mainindex == ft_strlenu(g_mainline))
		paste_no_insert(str, mainindex, prompt);
	else
		paste_insert(mainindex, str, pos, prompt);
}

void	ft_copy_paste(char *buf, int **prompt, int *mainindex, int **pos)
{
	static char	*str;

	if (buf[0] == 11)
	{
		str ? free(str) : 0;
		str = ft_strdup(g_mainline);
		clean(prompt[0], mainindex, pos[0]);
		free(g_mainline);
		g_mainline = ft_strnew(1);
	}
	else if (buf[0] == 12)
	{
		str ? free(str) : 0;
		str = ft_strdup(g_mainline);
	}
	else if (str && buf[0] == 16 && !ft_occur(g_mainline, '\n')
			&& !ft_occur(str, '\n'))
		paste(str, prompt, mainindex, pos);
	else if (buf[0] == 127)
		delete_c(pos, prompt[0], mainindex, 1);
	else if (buf[0] == 4 || (buf[0] == 27 && buf[1] == 91 && buf[2] == '3'
		&& buf[3] == '~'))
		delete_c(pos, prompt[0], mainindex, -1);
}
