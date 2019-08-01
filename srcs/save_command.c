/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/30 00:23:47 by lubenard          #+#    #+#             */
/*   Updated: 2019/08/01 13:00:44 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh21.h>

void		history(t_hist *lkd_hist)
{
	static int	i = 1;
	int			tmp;

	tmp = 0;
	while (lkd_hist->prev && tmp != 15)
	{
		lkd_hist = lkd_hist->prev;
		tmp++;
	}
	while (lkd_hist)
	{
		if (i < 10)
			ft_putstr("    ");
		else if (i < 100)
			ft_putstr("   ");
		else if (i < 1000)
			ft_putstr("  ");
		else if (i < 100000)
			ft_putstr(" ");
		ft_putnbr(i++);
		ft_putstr("  ");
		ft_putendl(lkd_hist->history);
		lkd_hist = lkd_hist->next;
	}
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

void		write_history(char *command, char *path)
{
	int		file;
	char	*history_path;

	history_path = ft_strjoin(path, "/.history");
	if (access(history_path, F_OK) == -1)
	{
		file = open(history_path, O_CREAT | O_RDWR, S_IWUSR | S_IRUSR);
		ft_putendl_fd(command, file);
		close(file);
	}
	else
	{
		file = open(history_path, O_RDWR | O_APPEND);
		ft_putendl_fd(command, file);
		close(file);
	}
	free(history_path);
}

void		save_command(t_hustru *big_struc, char *command)
{
	t_hist *new_element;
	t_hist *lkd_hist;

	new_element = NULL;
	lkd_hist = big_struc->lkd_hist;
	if (!ft_strcmp(lkd_hist->history, "") && !lkd_hist->prev)
		ft_strcpy(lkd_hist->history, command);
	else
	{
		new_element = new_maillon_hist();
		ft_strcpy(new_element->history, command);
		lkd_hist->next = new_element;
		new_element->prev = lkd_hist;
		lkd_hist = lkd_hist->next;
		big_struc->lkd_hist = new_element;
	}
	write_history(command, ".");
}
