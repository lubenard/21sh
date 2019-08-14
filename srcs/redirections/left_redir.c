/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   left_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/17 15:59:55 by lubenard          #+#    #+#             */
/*   Updated: 2019/08/14 16:12:12 by lubenard         ###   ########.fr       */
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

int		arrow_left(t_hustru *big_struc, char *command)
{
	char	**tab;
	int		i;
	int		fd;
	char	*first_command;
	char	*trimmed_str;

	tab = ft_strsplit(command, '<');
	i = 1;
	while (tab[i])
	{
		trimmed_str = ft_strtrim(tab[i]);
		printf("Tab[i] vaut %s\n", tab[i++]);
		if (access(trimmed_str, F_OK) == -1)
			return (print_error_redirect(tab, trimmed_str));
		else
		{
			free(tab[i]);
			tab[i] = trimmed_str;
		}
		i++;
	}
	first_command = extract_first(command, '<');
	printf("first_command = %s\n", first_command);
	i = 1;
	while (tab[i])
	{
		fd = open(trimmed_str, O_RDONLY);
		dup2(fd, 0);
		close(fd);
		basic_command(big_struc, first_command);
		i++;
	}
	ft_deltab(tab);
	free(first_command);
	return (0);
}
