/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_edition.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymarcill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/16 15:03:03 by ymarcill          #+#    #+#             */
/*   Updated: 2019/08/01 15:13:19 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <input.h>
#include <sh21.h>

void	init_esc_seq()
{
	char	*cursor_pos_s;

	cursor_pos_s = "\e[s";
	ft_putstr(cursor_pos_s);
	if (tgetent(NULL, getenv("TERM")) == 0)
		ft_putstr("ERROR");
}

void	manage_tab(char *buf)
{
	if (buf[0] == 9)
		ft_putstr("tab");
}

int		singleton(int stock, int action)
{
	static int	i = 0;

	//i = ;
	if (action)
	{
		i = stock;
	}
	return (i);	
}

void	signalHandler(int signal)
{
	ft_putnbr(signal);
	if (signal == SIGINT)
		singleton(signal, 1);
}

char	*ft_copy_paste(char *line, char *buf, int **prompt, int *i)
{
	static char 	*str;
	int				*coord;
	int				*newcoord;
	int				r;
	int				k;
	int				j;
	int				t;
	struct winsize	w;
	char *tmp = NULL;
	
	k = 0;
	j = 0;
	t = 0;
	ioctl(0, TIOCGWINSZ, &w);
	r = get_row(0, ft_strlenu(line), prompt[0][1]);
	coord = get_coord(get_cursor_position());
	if (buf[0] ==  11)
	{
		str ? free(str) : 0;
		str = ft_strdup(line);
		*i -= ft_strlenu(str);
		clean(ft_strlenu(line), prompt[0], r);
		free(line);
		line = ft_strnew(1);
	}
	else if (buf[0] == 12)
	{
		str ? free(str) : 0;
		str = ft_strdup(line);
	}
	else if (str && buf[0] == 16)
	{
		if ((coord[1] >= ft_strlenu(line) + prompt[0][1] && r == 0) ||
		(coord[1] >= (ft_strlenu(line) + prompt[0][1]) - w.ws_col * r && r > 0)
	   || (coord[1] == 1 && coord[0] == w.ws_row))
		{
			//ft_putstr("COCOU");
			go_last_char(ft_strlenu(line), prompt[0]);
			ft_putstr(str);
			newcoord = get_coord(get_cursor_position());
			t = get_row(0, ft_strlenu(line), prompt[0][1]);
			line = ft_strjoinnf(line, str);
			*i += ft_strlenu(str);
			r = get_row(0, ft_strlenu(line), prompt[0][1]);
			if (newcoord[1] == w.ws_col || coord[1] == w.ws_col)// && newcoord[0] != prompt[0])
			{
				if (coord[0] == w.ws_row)
				{
					ft_putstr("\e[S");
					if (r > 0 && r > t)
						prompt[0][0] = prompt[0][0] - (r - t);
				}
				ft_putstr("\e[E");
			}
		}
		else
		{
			clean(ft_strlenu(line), prompt[0], r);
			tmp = malloc(sizeof(char) * ft_strlenu(line) + ft_strlenu(str) + 102);
			while (line[k])
			{
				if ((k == coord[1] - prompt[0][1] && prompt[0][0] == coord[0]) ||
				(coord[0] > prompt[0][0] && k == coord[1] + (w.ws_col*(coord[0]
				-prompt[0][0])	- prompt[0][1])))
				{
					while (str[t])
						tmp[j++] = str[t++];
					//tmp[j] = '\0';
					//tmp = ft_strjoinnf(tmp, str);
					//j += ft_strlenu(str);
					//j++;
				}
				tmp[j] = line[k++];
				j++;
			}
			tmp[j] = '\0';
			ft_putstr(tmp);
			newcoord = get_coord(get_cursor_position());
			if (newcoord[1] > coord[1])
			{
				while (newcoord[1]-- > (coord[1] + ft_strlenu(str)))
					ft_putchar('\b');
			}
			else
			{
				while (newcoord[1]++ < coord[1])
							ft_putstr("\e[C");
			}
			if (newcoord[0] > coord[0])
			{
				while (newcoord[0]-- > coord[0])
					ft_putstr("\e[B");
			}
			else
			{
				while (newcoord[0]++ < coord[0])
					ft_putstr("\e[A");
			}
			free(line);
			line = ft_strdup(tmp);
			r = get_row(0, ft_strlenu(line), prompt[0][1]);
			if (w.ws_row - prompt[0][0] < r)
				prompt[0][0] -= r - (w.ws_row - prompt[0][0]);
		}
	}
	if (buf[0] == 127)
	{
		tmp = ft_strdup(line);
		line = ft_strdup(delete_c(r, prompt[0], line, i));
		if (ft_strcmp(tmp, line) != 0)
			*i = *i - 1;
	}
	return (line);
}

char	*test1(int index, char *buf, char *line, int **prompt)
{
	int		*coord;
	int		*newcoord;
	char	*str;
	struct winsize w;
	int		r;
	int		i;
	int		j;

	i = 0;
	j = 0;
	ioctl(0, TIOCGWINSZ, &w);
	str = malloc(sizeof(char) * index + 102);
	r = get_row(0, ft_strlenu(line), prompt[0][1]);
	coord = get_coord(get_cursor_position());
	//if (*prompt[0]== w.ws_row && r > 0)
	//	*prompt[0] = prompt[0] - r;
	if ((coord[1] >= index + prompt[0][1] && r == 0) ||
		(coord[1] >= (index + prompt[0][1]) - w.ws_col * r && r > 0)
	   || (coord[1] == 1 && coord[0] == w.ws_row))
	{
		line = ft_strjoinnf(line, buf);
		ft_putstr(buf);
		if (coord[1] == w.ws_col)
		{
			if (coord[0] == w.ws_row)
			{
				ft_putstr("\e[S");
				prompt[0][0] -= 1;
			}
			ft_putstr("\e[E");
		}
	}
	else
	{
		clean(ft_strlenu(line), prompt[0], r);
		while (line[i])
		{
			if ((i == coord[1] - prompt[0][1] && prompt[0][0] == coord[0]) ||
				(coord[0] > prompt[0][0] && i == coord[1] + (w.ws_col*(coord[0]
				-prompt[0][0]) - prompt[0][1])))
			{
				str[j++] = buf[0];
			}
			str[j] = line[i++];
			j++;
		}
		str[j] = '\0';
		ft_putstr(str);
		i = j + prompt[0][1];
		newcoord = get_coord(get_cursor_position());
	/*	if (newcoord[1] == w.ws_col && newcoord[0] == w.ws_row)
		{
			ft_putstr("\e[S");
		//	ft_putstr("\e[E");
		}*/
		if (coord[1] == w.ws_col && coord[0] > prompt[0][0])
		{
				i = newcoord[1];
				while (i-- > 1)
					ft_putchar('\b');
				i = newcoord[0];
				while (i-- > coord[0] + 1)
					ft_putstr("\e[F");
				i = 0;
		}
		if (coord[0] > prompt[0][0] && coord && i != 0)
		{
			i = newcoord[1];
			if (i >= coord[1])
			{
				while (i-- > coord[1] + 1)
					ft_putchar('\b');
			}
			else if (i < coord[1])
			{
				while (i++ < coord[1] + 1)
					ft_putstr("\e[C");
			}
			i = newcoord[0];
			while (i-- > coord[0] && coord[1] != w.ws_col)
				ft_putstr("\e[A");
		}
		else if (coord[0] == prompt[0][0] && i != 0)
		{
			while (i-- > coord[1] + 1)
				ft_putchar('\b');
		}
		free(line);
		line = ft_strdup(str);
		r = get_row(0, ft_strlenu(line), prompt[0][1]);
		if (w.ws_row - prompt[0][0] < r)
			prompt[0][0] -= r - (w.ws_row - prompt[0][0]);
//		ft_putnbr(prompt[0][0]);
	}
	return (line);
}

int		ft_read_1(t_hustru *big_struc, const int fd, char **line)
{
	char	buf[9];
	int		ret;
	int		*prompt;
	int		*coord;
	struct  winsize w;
	int		r;
	int		t;
	int		i;
	int		cmax;
	int		check;

	r = 0;
	i = 0;
	check = 0;
	coord = NULL;
	ioctl(0, TIOCGWINSZ, &w);
	cmax = w.ws_col;
	//apl fonction : READ 1e char si ctrl-D apl fonction de gestion ctrl-D
	*line = ft_strnew(1);
	init_esc_seq();
	if (set_none_canon_mode(fd) == -1 )//|| signal(SIGINT, signalHandler) == SIG_ERR)
	{
		free(*line);
		return (-1);
	}
	prompt = get_coord(get_cursor_position());
	while (42)
	{
		bzero(buf, sizeof(buf));
		if ((ret = read(fd, buf, 8)) == -1 || buf[0] == 'q' || (buf[0] == 4 && !buf[1] && !*line[0]))
		{
			ft_putstr("exit");
			reset_shell_attr(fd);
			free(*line);
			return (-1);
		}
		buf[ret] = '\0';
		coord = get_coord(get_cursor_position());
		if (buf[0] == 3 && !buf[1])
		{
			ft_putstr("\n\r");
			return (0);
		}
		if (coord[0] == 1)
			prompt[0] = 1;
		if (buf[0] != '\n' && buf[0] > 31 && buf[0] > 0 && buf[0] < 127)
		{
			*line = test1(i, buf, *line, &prompt);
			i = ft_strlenu(*line);
		}
		r = get_row(0, ft_strlenu(*line), prompt[1]);
		move_with_arrows(buf, ft_strlenu(*line), prompt, r);
		manage_tab(buf);
		move_toword(*line, buf, prompt);
		*line = ft_copy_paste(*line, buf, &prompt, &i);
		*line = move_hist(buf, *line, &prompt, big_struc->lkd_hist);
		if (buf[0] == '\n')
		{
			t = r;
			if (coord[0] >= prompt[0] && 
					coord[0] < prompt[0] + r)
				t = coord[0] - prompt[0];
			while (t++ < r)
				ft_putstr("\e[B");
			ft_putstr("\n\r");
			*line = get_quotes(*line, big_struc->lkd_hist);
		//	if (tmp[0] && lkd_hist && ft_strcmp(lkd_hist->history, tmp))
			save_command(big_struc, *line);
			free(coord);
			free(prompt);
			return (0);						//ma line si il y a deja un caractere									
		}									// pour la tabulation (autocpletion)				
		free(coord);
	}
	return (0);
}
