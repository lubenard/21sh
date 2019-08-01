/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_cursor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymarcill <ymarcill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/01 18:08:37 by ymarcill          #+#    #+#             */
/*   Updated: 2019/08/01 18:09:13 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <input.h>

void	go_first_char(int *prompt, int i, int r)
{
	int		*coord;
	int		*newcoord;
	int		c;
	struct	winsize	w;

	ioctl(0, TIOCGWINSZ, &w);
	(void)i;
	coord = get_coord(get_cursor_position());
	if (coord[0] == prompt[0] && r > 0 &&prompt[1] == coord[1])
		return ;
	c = coord[1];
	/*ft_putnbr(coord[0]);
	ft_putnbr(prompt[0]);
	ft_putnbr(r);*/
	if (coord[0] == 1 || coord[0] == prompt[0])
	{
		while (c-- > prompt[1])
			ft_putchar('\b');
	}
	else
	{
		ft_putstr("\e[u");
		newcoord = get_coord(get_cursor_position());
		//ft_putnbr(r);
		//ft_putnbr(coord[0]);
		if (prompt[0] == 1)
		{
			c = 0;
			while (c++ < prompt[1] - 1)
				ft_putstr("\e[C");
		}
		else if (coord[0] == w.ws_row)
		{
			c = 0;
			while (c++ < r)
				ft_putstr("\e[A");
		}
		else if (coord[0] == prompt[0] + r)
		{
			c = newcoord[0];
			while (c-- > prompt[0])
				ft_putstr("\e[A");
		}
	}
	free(coord);
}

void	left_arrow(int *prompt, int i)
{
	int	*coord;
	struct	winsize w;
	int		tmp;
	int		r;
	int		x;

	ioctl(0, TIOCGWINSZ, &w);
	tmp = 0;
	x = prompt[0];
	r = get_row(0, i, prompt[1]);
	coord = get_coord(get_cursor_position());
	//ft_putnbr(coord[1]);
	if ((prompt[0] == w.ws_row || coord[0] == w.ws_row)&& r > 0)
		prompt[0] -= r;
	if ((coord[0] == prompt[0] && coord[1]  ==  prompt[1]) ||
		(coord[0] == 1 && coord[1] == prompt[1]))// || (prompt[0] == w.ws_row &&
		//coord[0] == (w.ws_row - r) && coord[1] == prompt[1]))
			ft_putstr("");
	else
	{
		if (coord[1] == 1)
		{
			ft_putstr("\e[A");
			while (tmp++ < w.ws_col)
				ft_putstr("\e[C");
		}
		else
			ft_putchar('\b');
	}
	coord ? free(coord) : 0;
	prompt[0] = x;
}

/*void	history_print(char *line, int *prompt, int r)
{
	clean(ft_strlenu(line), prompt, r);
}*/

void    move_with_arrows(char *buf, int i, int *prompt, int r)
{
    if (buf[0] == 27 && buf[1] == 91)
    {
        if (buf[2] == 68)
            left_arrow(prompt, i);
        else if (buf[2] == 67)
			right_arrow(i, prompt);
        /*apl fonction historique et SET une globale a 1 si historique ouvert*/
     //   else if (buf[2] == 65)
       //   history_print(line, prompt, r);
        /*si deja dans l'historique aller jusqu'a la fin sinon ne rien faire*/
       // else if (buf[2] == 66)
         //   ft_putstr("down historique");
    }
    if (buf[0] == 1)
        go_first_char(prompt, i, r);
    if (buf[0] == 5)
		go_last_char(i, prompt);
	/*coller en insert*/
	/*quotes*/
	/*historique*/
	/*tab*/
}

