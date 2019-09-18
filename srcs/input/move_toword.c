/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_toword.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymarcill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/20 17:15:57 by ymarcill          #+#    #+#             */
/*   Updated: 2019/09/18 17:24:36 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <input.h>

void	ft_prev_word(int *prompt, int *mainindex, int *pos)
{
	int		i;
	char	j;
	int		*coord;
	int		r;

	j = 0;
	i = 0;
	r = get_row(0, ft_strlenu(g_mainline), prompt[1]);
	coord = get_coord(get_cursor_position());
	while (g_mainline[i++])
		j = g_mainline[i] == ' ' ? 'y' : 0;
	if ((prompt[1] == coord[1] && coord[0] == prompt[0]) || j == 'y')
	{
		free(coord);
		return ;
	}
	if (prompt[0] != coord[0])
		i = coord[1] + (w.ws_col * (coord[0] - prompt[0]) - prompt[1]);
	else
		i = (coord[1]) - prompt[1];
	while ((i < ft_strlenu(g_mainline) && i >= 0 && g_mainline[i] == ' '))
	{
		left_arrow(mainindex, prompt, pos);
		i--;
	}
	while (i > 0 && g_mainline[i] != ' ')
	{
		left_arrow(mainindex, prompt, pos);
		i--;
	}
	free(coord);
}

void	ft_next_word(int *prompt, int *mainindex)
{
	int		i;
	char	j;
	int		*coord;
	int		r;
	int		x;

	j = 0;
	x = prompt[0];
	i = 0;
	r = get_row(0, ft_strlenu(g_mainline), prompt[1]);
	coord = get_coord(get_cursor_position());
	if (prompt[0] != coord[0])
		i = coord[1] + (w.ws_col * (coord[0] - prompt[0]) - prompt[1]);
	else
		i = (coord[1]) - prompt[1];
	while (g_mainline[i] && g_mainline[i] == ' ')
	{
		right_arrow(mainindex, ft_strlenu(g_mainline), prompt);
		i++;
	}
	while (g_mainline[i] && g_mainline[i] != ' ')
	{
		right_arrow(mainindex, ft_strlenu(g_mainline), prompt);
		i++;
	}
	free(coord);
	prompt[0] = x;
}

void	ft_prev_line(int *prompt, int *pos, int *mainindex)
{
	int *coord;

	coord = get_coord(get_cursor_position());
	if (coord[0] == 1 || ft_occur(g_mainline, '\n') || coord[0] == prompt[0])
	{
		free(coord);
		return ;
	}
	if (coord[0] - 1 == prompt[0] && coord[1] < prompt[1])
		go_first_char(mainindex, prompt, pos);
	else
	{
		if (coord[0] - 1 == prompt[0])
			*mainindex -= (w.ws_col);
		else
			*mainindex -= w.ws_col;
		ft_putstr_fd("\e[A", 0);
	}
	free(coord);
}

void	ft_next_line(int *prompt, int r, int *mainindex)
{
	int *coord;
	int x;
	int i;

	i = ft_strlenu(g_mainline);
	x = prompt[0];
	coord = get_coord(get_cursor_position());
	if (coord[0] == w.ws_row || ft_occur(g_mainline, '\n'))
	{
		free(coord);
		return ;
	}
	if (coord[0] < prompt[0] + r)
	{
		*mainindex += w.ws_col;
		ft_putstr_fd("\e[B", 0);
	}
	if (coord[0] + 1 == prompt[0] + r && coord[1] >
		(i + prompt[1] - (w.ws_col * r)))
		go_last_char(mainindex, ft_strlenu(g_mainline), prompt);
	free(coord);
	prompt[0] = x;
}

void	move_toword(char *buf, int *prompt, int *mainindex, int *pos)
{
	int r;

	r = get_row(0, ft_strlenu(g_mainline), prompt[1]);
	if (buf[0] == 2)
		ft_prev_word(prompt, mainindex, pos);
	else if (buf[0] == 14)
		ft_next_word(prompt, mainindex);
	else if (buf[0] == 21)
		ft_prev_line(prompt, pos, mainindex);
	else if (buf[0] == 6)
		ft_next_line(prompt, r, mainindex);
}
