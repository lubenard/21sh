/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   left_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/17 15:59:55 by lubenard          #+#    #+#             */
/*   Updated: 2019/08/13 19:50:48 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh21.h>

/*
** Send into input programm
*/

void	double_arrow_left(t_env *lkd_env, char *command)
{
	(void)command;
	(void)lkd_env;
}

void	arrow_left(t_hustru *big_struc, char *command)
{
	char	**tab;
	int		i;
	int		fd;
	char	*first_command;

	tab = ft_strsplit(command, ' ');
	i = 0;
	while (tab[i])
		i++;
	first_command = extract_first(command, '<');
	printf("first_command = %s\n", first_command);
	fd = open(tab[i - 1], O_RDONLY);
	dup2(fd, 0);
	close(fd);
	basic_command(big_struc, first_command);
	ft_deltab(tab);
	free(first_command);
}
