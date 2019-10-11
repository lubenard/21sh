/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_redir.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/02 14:50:16 by lubenard          #+#    #+#             */
/*   Updated: 2019/10/11 05:20:41 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh21.h>

int		is_digit(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (ft_isdigit(str[i++]))
			return (1);
	}
	return (0);
}

int		count_args_redir(char **tab, int i)
{
	int		elem;
	int		j;

	j = 0;
	elem = 0;
	while (tab[i + j])
	{
		if (!ft_strchr(tab[i + j], '>') && !ft_strchr(tab[i + j], '<'))
		{
			if (ft_strstr(tab[i + j - 1], "<&")
			|| ft_strstr(tab[i + j - 1], ">&"))
				elem++;
			else if (!ft_strchr(tab[i + j - 1], '>')
			&& !ft_strchr(tab[i + j - 1], '<'))
				elem++;
		}
		j++;
	}
	printf("\e[35m[Count args redir] Elem vaut %d\e[0m\n", elem + i);
	return (elem + i);
}

int		count_elem_redir(char **tab, int i)
{
	int		elem;
	int		j;

	j = 0;
	elem = 0;
	while (tab[i + j])
	{
		if (!ft_strchr(tab[i + j], '>') && !ft_strchr(tab[i + j], '<'))
		{
			if ((ft_strstr(tab[i + j - 1], "&>")
			|| ft_strchr(tab[i + j - 1], '>')
			|| ft_strchr(tab[i + j - 1], '<'))
			&& !ft_strstr(tab[i + j - 1], ">&")
			&& !ft_strstr(tab[i + j - 1], "<&")
			&& ft_strcmp(tab[i + j - 1], "<<"))
				elem++;
			else if (ft_strchr(tab[i + j - 1], '>')
			&& ft_strchr(tab[i + j - 1], '<'))
				elem++;
		}
		j++;
	}
	printf("\e[35m[Count elem redir] Elem vaut %d\e[0m\n", elem);
	return (elem);
}
