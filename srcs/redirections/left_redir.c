/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   left_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/17 15:59:55 by lubenard          #+#    #+#             */
/*   Updated: 2019/08/21 11:21:27 by lubenard         ###   ########.fr       */
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

// Bugged when typing things like "cat < auteur > file1"

int		arrow_left(t_hustru *big_struc, char *command)
{
	char	**tab;
	int		i;
	int		fd;
	char	*first_command;
	char	*trimmed_str;

	tab = ft_strsplit(command, '<');
	i = 0;
	while (tab[i])
		printf("Tab[i] vaut |%s|\n", tab[i++]);
	i = 1;
	while (tab[i])
	{
		printf("Je boucle %s\n", tab[i]);
		printf("Tab[i] vaut %s\n", tab[i]);
		trimmed_str = ft_strtrim(tab[i]);
		printf("Tab[i] vaut %s\n", trimmed_str);
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
	char **tab2 = ft_strsplit(first_command, ' ');
	printf("first_command = %s\n", first_command);
	i = 1;
	while (tab[i])
	{
		printf("2: Tab[%d] vaut %s\n",i, tab[i]);
		fd = open(tab[i], O_RDONLY);
		dup2(fd, 0);
		close(fd);
		basic_command(big_struc, tab2);
		i++;
	}
	ft_deltab(tab2);
	ft_deltab(tab);
	free(first_command);
	return (0);
}
