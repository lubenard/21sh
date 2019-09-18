/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_copy_cut_paste_del.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymarcill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/17 19:24:31 by ymarcill          #+#    #+#             */
/*   Updated: 2019/09/18 17:24:38 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <input.h>

void	paste_no_insert(char *str, int *mainindex, int **prompt)
{
	int		i;
	int		*coord;

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
	g_mainline = ft_strjoinnf(g_mainline, str);
}

void	paste_insert(int *mainindex, char *str, int **pos, int **prompt)
{
	char	*tmp;
	int		i;
	int		j;
	int		k;

	i = 0;
	j = 0;
	k = 0;
	tmp = malloc(sizeof(char) * (ft_strlenu(g_mainline) + ft_strlenu(str) + 2));
	while (g_mainline[i])
	{
		if (i == *mainindex)
		{
			while (str[k])
				tmp[j++] = str[k++];
		}
		tmp[j++] = g_mainline[i++];
	}
	tmp[j] = '\0';
	k = *mainindex;
	clean(prompt[0], mainindex, pos[0]);
	pos[0] = ft_print_line(tmp, pos, mainindex, prompt);
	g_mainline = ft_strdup(tmp);
	while (j-- > k + ft_strlenu(str))
		left_arrow(mainindex, prompt[0], NULL);
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
