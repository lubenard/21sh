/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_redir.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/02 14:50:16 by lubenard          #+#    #+#             */
/*   Updated: 2019/09/23 18:23:17 by lubenard         ###   ########.fr       */
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

int		ft_str_is_alpha(char *str, int i)
{
	if (ft_isalpha(str[i]))
		return (1);
	return (0);
}

int		count_elem_redir(char **tab, int i)
{
	int		elem;

	elem = 0;
	while (tab[i] && ft_strchr(tab[i], '>'))
		i++;
	i++;
	while (tab[i])
	{
		//printf("Je regarde %s\n", tab[i]);
		if (!ft_strchr(tab[i], '>'))
		{
		//	printf("Je rajoute %s\n", tab[i]);
			elem++;
		}
		i++;
	}
	printf("Elem vaut %d\n", elem);
	return (elem);
}
