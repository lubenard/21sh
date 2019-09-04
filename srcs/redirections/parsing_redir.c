/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_redir.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/02 14:50:16 by lubenard          #+#    #+#             */
/*   Updated: 2019/09/04 15:15:20 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh21.h>

void	ft_str_start_cat(char *dest, const char *src, int start)
{
	int k;

	k = 0;
	k = ft_strlen(dest);
	while (src[start])
		dest[k++] = src[start++];
	if (ft_isalnum(dest[k - 1]))
	{
		dest[k] = ' ';
		dest[k + 1] = '\0';
	}
	else
		dest[k] = '\0';
}

int		count_elem_redir(char **tab, int i)
{
	int elem;

	elem = 0;
	while (tab[i])
	{
		if (ft_strchr(tab[i], '>'))
			elem++;
		i++;
	}
	return (elem);
}

int		pass_filename(char **tab, int i)
{
	int e;

	e = 0;
	if (tab[i][0] == '>')
		e++;
	while (tab[i][e] == ' ' || tab[i][e] == '\t')
		e++;
	while (ft_isalnum(tab[i][e]))
		e++;
	while (tab[i][e] == ' ' || tab[i][e] == '\t')
		e++;
	return (e);
}
