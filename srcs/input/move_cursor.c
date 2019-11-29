/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_cursor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymarcill <ymarcill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/01 18:08:37 by ymarcill          #+#    #+#             */
/*   Updated: 2019/11/29 00:51:20 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <input.h>

void	go_first_char(int *mainindex, int *prompt, int *pos)
{
	int		mark;
	int		rep;

	(void)prompt;
	rep = 1;
	mark = *mainindex;
	if (mark <= 0 || mark > ft_strlenu(g_mainline))
		return ;
	while (mark > 0)
	{
		left_arrow(mainindex, pos);
		mark--;
	}
}

void	go_upleft(int rep)
{
	ft_putstr_fd("\e[F", 0);
	while (rep++ < g_w.ws_col)
		ft_putstr_fd("\e[C", 0);
}

void	left_arrow(int *mainindex, int *pos)
{
	int		rep;
	int		*coord;

	rep = 1;
	if (*mainindex <= ft_strlenu(g_mainline) && *mainindex > 0
	&& g_mainline[*mainindex - 1])
	{
		coord = get_coord(get_cursor_position());
		if (g_mainline[*mainindex - 1] == '\n' && pos)
		{
			ft_putstr_fd("\e[F", 0);
			while (rep++ < g_w.ws_col)
				ft_putstr_fd("\e[C", 0);
			while (rep-- > pos[*mainindex - 1] + 1)
				ft_putchar_fd('\b', 0);
		}
		else if (coord[1] == 1)
			go_upleft(rep);
		else
			ft_putchar_fd('\b', 0);
		*mainindex -= 1;
		free(coord);
	}
}

void	move_with_arrows(char *buf, int *prompt, int *mainindex, int *pos)
{
	int r;

	r = get_row(0, ft_strlenu(g_mainline), prompt[1]);
	if (buf[0] == 27 && buf[1] == 91)
	{
		if (buf[2] == 68)
			left_arrow(mainindex, pos);
		else if (buf[2] == 67)
			right_arrow(mainindex, ft_strlenu(g_mainline), prompt);
	}
	if (buf[0] == 1 || (buf[0] == 27 && buf[1] == 91 && buf[2] == 'H'))
		go_first_char(mainindex, prompt, pos);
	if (buf[0] == 5 || (buf[0] == 27 && buf[1] == 91 && buf[2] == 'F'))
		go_last_char(mainindex, ft_strlenu(g_mainline), prompt);
}
