/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/30 00:23:47 by lubenard          #+#    #+#             */
/*   Updated: 2019/11/20 10:44:34 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh21.h>

int			history(t_hist *lkd_hist)
{
	int			tmp;

	tmp = 0;
	while (lkd_hist->prev)
	{
		lkd_hist = lkd_hist->prev;
		tmp++;
	}
	while (lkd_hist->next)
	{
		if (lkd_hist->index < 10)
			ft_putstr("    ");
		else if (lkd_hist->index < 100)
			ft_putstr("   ");
		else if (lkd_hist->index < 1000)
			ft_putstr("  ");
		else if (lkd_hist->index < 100000)
			ft_putstr(" ");
		ft_putnbr(lkd_hist->index);
		ft_putstr("  ");
		ft_putendl(lkd_hist->history);
		lkd_hist = lkd_hist->next;
	}
	return (0);
}

t_hist		*new_maillon_hist(void)
{
	t_hist *new_element;

	if (!(new_element = (t_hist *)malloc(sizeof(t_hist))))
		return (NULL);
	ft_bzero(new_element->history, 131073);
	new_element->next = NULL;
	new_element->prev = NULL;
	return (new_element);
}

int			write_history(char *command, char *history_path)
{
	int				file;

	if (access(history_path, F_OK) == -1)
		file = open(history_path, O_CREAT | O_WRONLY);
	else
		file = open(history_path, O_RDWR | O_APPEND);
	if (file == -1)
		return (display_error("Impossible to write at: ", history_path));
	ft_putendl_fd(command, file);
	close(file);
	return (0);
}

void		save_command(t_hustru *big_struc, char *command, int save)
{
	t_hist			*new_element;
	t_hist			*lkd_hist;
	static int		index = 1;

	lkd_hist = big_struc->lkd_hist;
	new_element = new_maillon_hist();
	ft_strcpy(new_element->history, command);
	new_element->index = index++;
	new_element->next = lkd_hist;
	if (!lkd_hist->prev && !lkd_hist->next)
		lkd_hist->prev = new_element;
	else
	{
		lkd_hist->prev->next = new_element;
		new_element->prev = lkd_hist->prev;
		lkd_hist->prev = new_element;
	}
	if (save == 1)
		write_history(command, big_struc->history_path);
}
