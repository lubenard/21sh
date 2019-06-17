/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   go_last_char.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/17 12:12:54 by lubenard          #+#    #+#             */
/*   Updated: 2019/06/17 12:12:56 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <input.h>

void    go_last_char_underft(int pc, int c, int y, int cc)
{
	(void)pc;
    if (cc > c)
    {
        while (y-- > c)
            ft_putstr("\e[D");
    }
    else
    {
        while (y++ < c && cc < c)
            ft_putstr("\e[C");
    }
}

int     go_last_row(int tmp, int maxc, int r)
{
    while (tmp > maxc)
    {
        tmp = tmp - maxc;
        r++;
    }
    return (r);
}

void    init_var(int **coord, int *x, int *y)
{
    if (!((coord[0]) = get_coord(get_cursor_position())))
        return ;
    *y = coord[0][1];
    *x = coord[0][0];
}

void    simple_line(int y, int pr, int i, int c)
{
    while (y++ < (pr + i) && c < (pr + i))
        ft_putstr("\e[C");
}
 void    go_last_char(int i, int *prompt)
 {
     struct  get_prompt_pos  gpt;
     struct winsize w;

     ioctl(0, TIOCGWINSZ, &w);
     init_var(&gpt.coord, &gpt.x, &gpt.y);
     gpt.c = i;
     gpt.tmp = 0;
	 gpt.r = get_row(0, i, prompt[1]);
//	ft_putnbr(gpt.r);
     if (i == 0)
         return ;
     if (i > w.ws_col - (prompt[1]))
     {
         gpt.c = i - (w.ws_col - (prompt[1]));
         gpt.tmp = gpt.c;
         if (gpt.c > w.ws_col)
             gpt.c = (i - (w.ws_col - (prompt[1]))) % w.ws_col;
	//	ft_putnbr(prompt[0] + gpt.r);
	//	ft_putnbr(gpt.x);
	//	ft_putnbr(gpt.r);
         while (gpt.x++ < prompt[0] + gpt.r)
			gpt.r > 0 ? ft_putstr("\e[B") : 0;
         go_last_char_underft(prompt[1], gpt.c, gpt.y, gpt.coord[1]);
     }
    else if (i <= w.ws_col - prompt[1])
	{	
		simple_line(gpt.y, prompt[1], i, gpt.coord[1]);
		if (i == w.ws_col - prompt[1] + 1)
			ft_putstr("\e[C");
	}
}
 
