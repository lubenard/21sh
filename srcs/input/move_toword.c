/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_toword.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/17 12:13:40 by lubenard          #+#    #+#             */
/*   Updated: 2019/06/17 15:11:56 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <input.h>

void 	ft_prev_word(char *line, int *prompt)
{
	int i;
	char	j;
	int	*coord;
	int	r;
	int	x;
	struct winsize	w;

	j = 0;
	i = 0;
	x = prompt[0];
	ioctl(0, TIOCGWINSZ, &w);
	r = get_row(0, ft_strlenu(line), prompt[1]);
	coord = get_coord(get_cursor_position());
	if ((prompt[0] == w.ws_row || coord[0] == w.ws_row)&& r > 0)
	    prompt[0] -= r;
	while (line[i++])
		j = line[i] == ' ' ? 'y' : 0;
	if ((prompt[1] == coord[1] && coord[0] == prompt[0]) || j == 'y')
		return ;
	if (prompt[0] != coord[0])
		i = coord[1] + (w.ws_col*(coord[0] - prompt[0]) - prompt[1]);
	else
		i = (coord[1]) - prompt[1];
	while ((i < ft_strlenu(line) && i >= 0 && line[i] == ' '))
	{
		ft_putchar('\b');
		i--;
	}	
	while (i > 0 && line[i] != ' ')
	{
		ft_putchar('\b');
		i--;
	}
	prompt[0] = x;
	free(coord);
}

void	ft_next_word(char *line, int *prompt)
{
	int i;
	char	j;
	int	*coord;
	int	r;
	int	x;
	struct winsize	w;

	j = 0;
	x = prompt[0];
	i = 0;
	ioctl(0, TIOCGWINSZ, &w);
	r = get_row(0, ft_strlenu(line), prompt[1]);
	coord = get_coord(get_cursor_position());
	if ((prompt[0] == w.ws_row || coord[0] == w.ws_row)&& r > 0)
		prompt[0] -= r;
	while (line[i++])
		j = line[i] == ' ' ? 'y' : 0;
	if (j == 'y')
		return ;
	if (prompt[0] != coord[0])
		i = coord[1] + (w.ws_col*(coord[0] - prompt[0]) - prompt[1]);
	else
		i = (coord[1]) - prompt[1];
	while (line[i] && line[i] == ' ')
	{
		right_arrow(ft_strlenu(line), prompt);;
		i++;
	}	
	while (line[i] && line[i] != ' ')
	{
		right_arrow(ft_strlenu(line), prompt);;
		i++;
	}
	free(coord);
	prompt[0] = x;

}

void	ft_prev_line(int *prompt, int r)
{
	int				*coord;
	struct winsize	w;
	int	x;
	int				i;

	i = 0;
	x = prompt[0];
	ioctl(0, TIOCGWINSZ, &w);
	coord = get_coord(get_cursor_position());
	if ((prompt[0] == w.ws_row || coord[0] == w.ws_row)&& r > 0)
		prompt[0] = prompt[0] - r;
	if (coord[0] == 1)
	{
		free(coord);
		return ;
	}
	if (coord[0] - 1 == prompt[0] && coord[1] < prompt[1])
	{
		i = coord[1];
		while (i++ < prompt[1])
			ft_putstr("\e[C");
	}
	if (coord[0] > prompt[0])
		ft_putstr("\e[A");
	free(coord);
	prompt[0] = x;
}

void	ft_next_line(char *line, int *prompt, int r)
{
	int				*coord;
	struct winsize	w;
	int	x;
	int				i;

	i = ft_strlenu(line);
	x = prompt[0];
	ioctl(0, TIOCGWINSZ, &w);
	coord = get_coord(get_cursor_position());
	if (coord[0] == w.ws_row)
	{
		free(coord);
		return ;
	}
	if ((prompt[0] == w.ws_row || coord[0] == w.ws_row)&& r > 0)
		prompt[0] = prompt[0] - r;
	if (coord[0] < prompt[0] + r)
		ft_putstr("\e[B");
	if (coord[0] + 1 == prompt[0] + r && coord[1] > (i + prompt[1] - (w.ws_col * r)))
		go_last_char(ft_strlenu(line), prompt);
	free(coord);
	prompt[0] = x;
}

void	move_toword(char *line, char *buf, int *prompt)
{
	int r;

	r = get_row(0, ft_strlenu(line), prompt[1]);
	if (buf[0] == 2)
		ft_prev_word(line, prompt);
	else if (buf[0] == 14)
		ft_next_word(line, prompt);
	else if (buf[0] == 21)
		ft_prev_line(prompt, r);
	else if (buf[0] == 6)
		ft_next_line(line, prompt, r);
}
