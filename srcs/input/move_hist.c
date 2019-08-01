/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_hist.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymarcill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/20 17:50:59 by ymarcill          #+#    #+#             */
/*   Updated: 2019/08/01 18:42:55 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <input.h>

int		get_nb_line_quote(char *str)
{
	int	i;
	int	nb;

	i = 0;
	nb = 0;
	while (str[i++])
	{
		if (str[i] == '\n')
			nb++;
	}
	return (nb);
}

void	clean_for_quotes(char *line, int *prompt, int r)
{
	int	i;
	int gnbl;

	i = 0;
	go_first_char(prompt, ft_strlenu(line), r);
	ft_putstr("\e[0K");
	gnbl = get_nb_line_quote(line);
	if (get_nb_line_quote(line) == 0)
		gnbl = r;
	while (i++ < gnbl)
	{
		ft_putstr("\e[B");
		ft_putstr("\e[2K");
	}
	go_first_char(prompt, ft_strlenu(line), r);
}

char	*history_prev(char *line, int **prompt, t_hustru *big_struc)
{
	int	r;
	char	*tmp;
	struct	winsize w;

	ioctl(0, TIOCGWINSZ, &w);
	tmp = ft_strdup(line);
	r = get_row(0, ft_strlenu(line), prompt[0][1]);
	if (big_struc->lkd_hist && big_struc->lkd_hist->history[0])
	{
		clean_for_quotes(line, *prompt, r);
		free(tmp);
		tmp = ft_strdup(big_struc->lkd_hist->history);
		ft_putstr(tmp);
	}
	//printf("\nJe suis sur %s\n", big_struc->lkd_hist->history);
	if (big_struc->lkd_hist && big_struc->lkd_hist->prev)
		big_struc->lkd_hist = big_struc->lkd_hist->prev;
	r = get_row(0, ft_strlenu(tmp), prompt[0][1]);
	if (w.ws_row - prompt[0][0] < r)
		prompt[0][0] -= r -(w.ws_row - prompt[0][0]);
	return (tmp);
}

char	*history_next(char *line, int **prompt, t_hustru *big_struc)
{
	int	r;
	int nr;
	char	*tmp;
	struct	winsize	w;

	nr = 0;
	ioctl(0, TIOCGWINSZ, &w);
	tmp =ft_strdup(line);
	r = get_row(0, ft_strlenu(line), prompt[0][1]);
	if (big_struc->lkd_hist && big_struc->lkd_hist->history[0])
		clean_for_quotes(line, *prompt, r);
	if (big_struc->lkd_hist && big_struc->lkd_hist->next)
	{
		big_struc->lkd_hist = big_struc->lkd_hist->next;
		free(tmp);
		tmp = ft_strdup(big_struc->lkd_hist->history);
		ft_putstr(tmp);
		r = get_row(0, ft_strlenu(tmp), prompt[0][1]);
		if (w.ws_row - prompt[0][0] < r)
			prompt[0][0] -= r -(w.ws_row - prompt[0][0]);
	}
	else if (big_struc->lkd_hist && big_struc->lkd_hist->history[0])
	{
		free(tmp);
		tmp = ft_strdup("");
	}
	return (tmp);
}

char	*move_hist(char *buf, char *line, int **prompt, t_hustru *big_struc)
{
	char	*tmp;

	tmp = ft_strdup(line);
	if (buf[0] == 27 && buf[1] == 91 && buf[2] == 65)
	{
		free(line);
		line = ft_strdup(history_prev(tmp, prompt, big_struc));
	}
	else if (buf[0] == 27 && buf[1] == 91 && buf[2] == 66)
	{
		free(line);
		line = ft_strdup(history_next(tmp, prompt, big_struc));
	}
	if (buf[0] == '\n')
	{
		while (big_struc->lkd_hist && big_struc->lkd_hist->next != NULL)
			big_struc->lkd_hist = big_struc->lkd_hist->next;
	}
	return (line);
}

