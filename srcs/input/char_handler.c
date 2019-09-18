/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymarcill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/17 19:14:38 by ymarcill          #+#    #+#             */
/*   Updated: 2019/09/18 17:38:17 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <input.h>

void		add_char(int *mainindex, char *buf, int **prompt)
{
	int		*coord;
	char	*tmp;

	tmp = ft_strdup(g_mainline);
	coord = get_coord(get_cursor_position());
	free(g_mainline);
	g_mainline = ft_strjoin(tmp, buf);
	free(tmp);
	ft_putstr_fd(buf, 0);
	*mainindex += 1;
	if (coord[1] == w.ws_col)
	{
		if (coord[0] == w.ws_row)
		{
			ft_putstr_fd("\e[S", 0);
			prompt[0][0] -= 1;
		}
		ft_putstr_fd("\e[E", 0);
	}
	free(coord);
}

char		*forthenorm(int check, char *str)
{
	char	*tmp;

	tmp = NULL;
	if (check == 1)
	{
		free(g_mainline);
		g_mainline = ft_strdup(str);
	}
	else
	{
		if ((tmp = malloc(sizeof(char) * (ft_strlenu(g_mainline) + 2))) == NULL)
			return (NULL);
		tmp != NULL ? ft_bzero(tmp, ft_strlenu(g_mainline) + 2) : 0;
	}
	return (tmp);
}

int			print_newline(int **prompt, char *str, int *mainindex, int **pos)
{
	int *coord;
	int i;

	i = 0;
	coord = malloc(sizeof(int) * 2);
	coord[0] = prompt[0][0];
	coord[1] = prompt[0][1] - 1;
	while (str[i])
	{
		coord[1]++;
		ft_putchar_fd(str[i], 0);
		if (i > 0 && str[i - 1] == '\n')
		{
			coord[1] = 1;
			coord[0]++;
		}
		pos[0][i] = coord[1];
		*mainindex += 1;
		coord = last_line_col(coord, prompt, str[i]);
		i++;
	}
	free(coord);
	forthenorm(1, str);
	free(str);
	return (i);
}

int			*insert_char(int *mainindex, char *buf, int **prompt, int **pos)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	j = 0;
	if ((str = forthenorm(0, NULL)))
		return (NULL);
	while (g_mainline[i])
	{
		if (i == *mainindex)
			str[j++] = buf[0];
		else if (j > ft_strlenu(g_mainline))
			break ;
		str[j++] = g_mainline[i++];
	}
	str[j] = '\0';
	free(pos[0]);
	pos = j != 0 ? malloc(sizeof(int) * j) : NULL;
	j = *mainindex;
	clean(prompt[0], mainindex, pos[0]);
	i = print_newline(prompt, str, mainindex, pos);
	while (i-- > j + 1)
		left_arrow(mainindex, prompt[0], pos[0]);
	return (pos[0]);
}

void		print_char(int *mainindex, char *buf, int **prompt, int **pos)
{
	pos[0] = NULL;
	if (*mainindex == ft_strlenu(g_mainline))
		add_char(mainindex, buf, prompt);
	else
		pos[0] = insert_char(mainindex, buf, prompt, pos);
}
