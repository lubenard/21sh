/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymarcill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/17 19:14:13 by ymarcill          #+#    #+#             */
/*   Updated: 2019/10/09 17:51:47 by ymarcill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <input.h>

int		get_row(int r, int i, int pc)
{
	int tmp;
	int *coord;

	coord = get_coord(get_cursor_position());
	if (coord[1] == 1)
		i++;
	tmp = i - (w.ws_col - pc) - 1;
	if (i > (w.ws_col - pc))
	{
		r++;
		while (tmp >= w.ws_col)
		{
			tmp -= w.ws_col;
			r++;
		}
	}
	free(coord);
	return (r);
}

void	clean(int *prompt, int *mainindex, int *pos)
{
	int r;
	int tmp;

	tmp = 0;
	r = get_row(0, ft_strlenu(g_mainline), prompt[1]);
	r += get_nb_line_quote(g_mainline);
	go_first_char(mainindex, prompt, pos);
	ft_putstr_fd("\e[0K", 0);
	while (tmp < r)
	{
		ft_putstr_fd("\e[B", 0);
		ft_putstr_fd("\e[2K", 0);
		tmp++;
	}
	while (tmp-- > 0)
		ft_putstr_fd("\e[A", 0);
}

int		*last_line_col(int *coord, int **prompt, char c)
{
	if (coord[1] == w.ws_col)
	{
		coord[1] = 0;
		if (coord[0] == w.ws_row)
		{
			prompt[0][0] -= 1;
			coord[0]++;
		}
		if (c != '\n')
		{
			ft_putstr_fd("a\b", 0);
			ft_putchar_fd(127, 0);
			ft_putchar_fd('\b', 0);
		}
	}
	return (coord);
}

int		*ft_print_line(char *tmp, int **pos, int *mainindex, int **prompt)
{
	int i;
	int *coord;

	i = 0;
	free(pos[0]);
	if (!(pos[0] = malloc(sizeof(int) * ft_strlenu(tmp))))
		return (NULL);
	while (tmp[i])
	{
		coord = get_coord(get_cursor_position());
		pos[0][i] = coord[1];
		ft_putchar(tmp[i]);
		*mainindex += 1;
		last_line_col(coord, prompt, tmp[i]);
		free(coord);
		i++;
	}
	free(g_mainline);
	return (pos[0]);
}

int		*tab_malloc(int *pos, int i)
{
	free(pos);
	if (i)
	{
		if ((pos = malloc(sizeof(int) * i)) == NULL)
			return (NULL);
		return (pos);
	}
	else
		return (NULL);
}
