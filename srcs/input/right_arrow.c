/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   right_arrow.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/17 12:13:59 by lubenard          #+#    #+#             */
/*   Updated: 2019/06/17 12:14:01 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <input.h>

void    ra(int cc, int cmax, int r)
{
    if (cc == cmax && r > 0)
        ft_putstr("\e[E");
}

int     ra1(int tmp, int cmax, int r)
{
    while (tmp > cmax)
    {
        tmp = tmp - cmax;
        r++;
    }
    return (r);
}

void    ra2(int c, int pc, int i, int cmax)
{
	//ft_putnbr(c);
	//ft_putnbr(cmax);
    if ((c - pc) < i && i != 0 && c != cmax)
        ft_putstr("\e[C");
}

void    ra3_init(int r, int *tmp, int cc, int cm)
{
    *tmp = 0;
    ra(cc, cm, r);
}

void    right_arrow(int i, int *prompt)
{
    struct  get_prompt_pos  gpp;
    struct  winsize w;

    ioctl(0, TIOCGWINSZ, &w);
    if (!(gpp.coord = get_coord(get_cursor_position())))
        return ;
    gpp.c = i;
	gpp.r = get_row(0, i, prompt[1]);
	//ft_putnbr(gpp.r);
//	if (gpp.coord[0] - gpp.r <= 1)
//		prompt[0] = 1;
    ra3_init(gpp.r, &gpp.tmp, gpp.coord[1], w.ws_col);
    if (i > (w.ws_col - prompt[1]))
    {
        gpp.c = i - (w.ws_col - (prompt[1]));
        gpp.tmp = gpp.c - 1;
        if (gpp.c > w.ws_col)
        {
            gpp.c = (i - (w.ws_col - (prompt[1]))) % w.ws_col;
          //  gpp.r = ra1(gpp.tmp, w.ws_col, gpp.r);
        }
		gpp.coord[0] == w.ws_row? ra(gpp.coord[1], w.ws_col, gpp.r) : 0;
        if ((gpp.coord[0] == (prompt[0] + gpp.r)  && gpp.coord[1] == gpp.c) || i == 0 ||
			(gpp.coord[0] == w.ws_row && i > (w.ws_col - prompt[1]) && gpp.coord[1] == gpp.c) || ((gpp.coord[0] - gpp.r) == 1 && gpp.coord[1] == gpp.c) ||
		   	(gpp.coord[1] == w.ws_col && gpp.r > 0))
            ft_putstr("");
        else
            ft_putstr("\e[C");
    }
    else if (i <= w.ws_col - prompt[1])
        ra2(gpp.coord[1], prompt[1], i, w.ws_col);
}

