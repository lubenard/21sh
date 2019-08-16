/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tabchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/16 15:15:26 by lubenard          #+#    #+#             */
/*   Updated: 2019/08/16 15:24:11 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_tabchr(char **tab, int pattern)
{
	int i;

	i = 0;
	while (tab[i])
	{
		if (ft_strchri(tab[i++], pattern) > 0)
			return (1);
		else
			i++;
	}
	return (0);
}
