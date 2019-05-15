/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/30 00:23:47 by lubenard          #+#    #+#             */
/*   Updated: 2019/05/15 20:23:29 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

t_hist	*new_maillon_hist(void)
{
	t_hist *new_element;

	if (!(new_element = (t_hist *)malloc(sizeof(t_hist))))
		return (NULL);
	ft_bzero(new_element->history, 131072);
	new_element->next = NULL;
	new_element->prev = NULL;
	return (new_element);
}

void	save_command(t_hist *lkd_hist, char *command)
{
	while (lkd_hist)
	{
		lkd_hist = lkd_hist->next;
	}
}

void	write_history(char *command, char *path)
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
