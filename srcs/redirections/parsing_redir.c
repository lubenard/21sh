/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_redir.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/02 14:50:16 by lubenard          #+#    #+#             */
/*   Updated: 2019/09/30 17:49:44 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh21.h>

int		count_elem_redir(char **tab, int i)
{
	int		elem;
	int		j;

	j = 0;
	elem = 0;
	printf("[Count elem redir] I vaut %d\n", i);
	while (tab[i + j])
	{
		printf("[Count elem redir] Je regarde %s\n", tab[i + j]);
		if (!ft_strchr(tab[i + j], '>') && !ft_strchr(tab[i + j - 1], '>')
		&& !ft_strchr(tab[i + j], '<') && !ft_strchr(tab[i + j - 1], '<'))
		{
			printf("[Count elem redir] Je rajoute %s\n", tab[i + j]);
			elem++;
		}
		j++;
	}
	printf("[Count elem redir] Elem vaut %d\n", elem + i);
	return (elem + i);
}
