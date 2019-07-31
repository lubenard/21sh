/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_hist.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymarcill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/20 17:50:59 by ymarcill          #+#    #+#             */
/*   Updated: 2019/07/31 20:05:48 by ymarcill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/input.h"
#include <sh21.h>

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

char	*history_prev(char *line, int **prompt, t_hist **lkd_hist)
{
	int	r;
	char	*tmp;
	struct	winsize w;

	ioctl(0, TIOCGWINSZ, &w);
	tmp = ft_strdup(line);
	r = get_row(0, ft_strlenu(line), prompt[0][1]);
	if ((*lkd_hist) && (*lkd_hist)->history[0])
	{
		clean_for_quotes(line, *prompt, r);
		free(tmp);
		tmp = ft_strdup((*lkd_hist)->history);
		ft_putstr(tmp);
	}
	if ((*lkd_hist) && (*lkd_hist)->prev)
	{
		(*lkd_hist)= (*lkd_hist)->prev;
	}
	r = get_row(0, ft_strlenu(tmp), prompt[0][1]);
	if (w.ws_row - prompt[0][0] < r)
		prompt[0][0] -= r -(w.ws_row - prompt[0][0]);
	return (tmp);
}

char	*history_next(char *line, int **prompt, t_hist **lkd_hist)
{
	int	r;
	int nr;
	char	*tmp;
	struct	winsize	w;

	nr = 0;
	ioctl(0, TIOCGWINSZ, &w);
	tmp =ft_strdup(line);
	r = get_row(0, ft_strlenu(line), prompt[0][1]);
	if ((*lkd_hist) && (*lkd_hist)->history[0])
		clean_for_quotes(line, *prompt, r);
	if ((*lkd_hist) && (*lkd_hist)->next)
	{
		(*lkd_hist) = (*lkd_hist)->next;
		free(tmp);
		tmp = ft_strdup((*lkd_hist)->history);
		ft_putstr(tmp);
		r = get_row(0, ft_strlenu(tmp), prompt[0][1]);
		if (w.ws_row - prompt[0][0] < r)
			prompt[0][0] -= r -(w.ws_row - prompt[0][0]);
	}
	else if ((*lkd_hist) && (*lkd_hist)->history[0])
	{
		free(tmp);
		tmp = ft_strdup("");
	}
	return (tmp);
}

char	*move_hist(char *buf, char *line, int **prompt, t_hist **lkd_hist)
{
	char	*tmp;

	tmp = ft_strdup(line);
	if (buf[0] == 27 && buf[1] == 91 && buf[2] == 65)
	{
		free(line);
		line = ft_strdup(history_prev(tmp, prompt, lkd_hist));
	}
	else if (buf[0] == 27 && buf[1] == 91 && buf[2] == 66)
	{
		free(line);
		line = ft_strdup(history_next(tmp, prompt, lkd_hist));
	}
	if (buf[0] == '\n')
	{
		while ((*lkd_hist) && (*lkd_hist)->next != NULL)
			(*lkd_hist) = (*lkd_hist)->next;
	}
	return (line);
}

