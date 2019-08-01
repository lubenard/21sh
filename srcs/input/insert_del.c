/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insert_del.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymarcill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/20 17:13:06 by ymarcill          #+#    #+#             */
/*   Updated: 2019/08/01 11:44:14 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <input.h>

int		get_row(int r, int i, int pc)
{
	struct winsize 	w;
	int				tmp;
	int				*coord;

	ioctl(0, TIOCGWINSZ, &w);
	coord = get_coord(get_cursor_position());
	if (coord[1] == 1)
		i++;
	tmp = i - (w.ws_col - pc) - 1;
	if (i > (w.ws_col - pc))
	{
		r = r + 1;
		while (tmp >= w.ws_col)
		{
			tmp = tmp - w.ws_col;
			r = r + 1;
		}
	}
	return (r);
}

void	clean(int i, int *prompt, int r)
{
	struct winsize	w;
	int 			tmp;

	ioctl(0, TIOCGWINSZ, &w);
	tmp = 0;
	go_first_char(prompt, i, r);
	ft_putstr("\e[0K");
	if (i > (w.ws_col - prompt[1]))
	{
		while (tmp++ < r)
		{
			 ft_putstr("\e[B");
			 ft_putstr("\e[2K");
   		 }
   		 go_first_char(prompt, i, r);
	}
}

char	*delete_c(int r, int *prompt, char *line, int *sizel)
{
	int 			i;
	int				j;
	int				*coord;
	int				*newcoord;
	int				*acoord;
	char			*str;
	struct winsize 	w;
	int				tmp;
	int				tmp2;

	i = 0;
	j = 0;
	tmp = 0;
	tmp2 = 0;
	(void)sizel;
	ioctl(0, TIOCGWINSZ, &w);
	str = malloc(sizeof(char) * ft_strlen(line) + 1);
	coord = get_coord(get_cursor_position());
	if ((coord[1] <= prompt[1] && prompt[0] == coord[0])
		|| (coord[0] == 1 && coord[1] <= prompt[1]))
			ft_putstr("");
	else
	{
		clean(ft_strlenu(line), prompt, r);
		acoord = get_coord(get_cursor_position());
		while (line && line[i])
		{

			if ((i + prompt[1]) != coord[1] - 1 && prompt[0] == coord[0])
				tmp = 1;
			if ((i + prompt[1]) != (coord[1] - 1) + w.ws_col*(coord[0] - prompt[0]) && coord[0]
				> prompt[0]  && r > 0 )
			{
				tmp2 = 1;
			}
			if (tmp == 1 || tmp2 == 1)
				str[j++] = line[i];
			i++;
			tmp = 0;
			tmp2 = 0;
		}
		str[j] = '\0';
		ft_putstr(str);
		i = j + prompt[1];
		newcoord = get_coord(get_cursor_position());
		/*ft_putstr("PROMPT[0] : ");
		ft_putnbr(prompt[0]);
		ft_putchar('/');
ft_putstr("Acoord[0] : ");
		ft_putnbr(acoord[0]);
		ft_putchar('/');
		ft_putstr("Acoord[1] : ");
		ft_putnbr(acoord[1]);
		ft_putchar('/');
		ft_putstr("len str : ");
		ft_putnbr(ft_strlenu(str));
		ft_putchar('/');
		ft_putstr("len line : ");
		ft_putnbr(ft_strlenu(line));
		ft_putchar('/');
		ft_putstr("newcoo[1] : ");
		ft_putnbr(newcoord[1]);
		ft_putchar('/');
		ft_putstr("newcoo[0] : ");
		ft_putnbr(newcoord[0]);*/
		if ((coord[1] == 1 || coord[1] == 2)&& newcoord[1] == w.ws_col)
		{
			if (coord[1] == 2)
				ft_putstr("\e[E");
			i = 0;
		}
		if (coord[0] > prompt[0] && i != 0)
		{
			i = newcoord[1];
			if (i >= coord[1])
			{
				while (i-- > coord[1] - 1)
					ft_putchar('\b');
			}
			else if (i < coord[1])
			{
				while (i++ < coord[1] - 1)
					ft_putstr("\e[C");
			}
			i = newcoord[0];
			while (i-- > coord[0])
				ft_putstr("\e[A");
		}
		else if (coord[0] == prompt[0])
		{
			while (i-- > coord[1] - 1)
				ft_putchar('\b');
		}
		free(newcoord);
		free(line);
		return (str);
	}
	free(coord);
	return (line);
}

















