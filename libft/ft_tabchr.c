/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tabchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/16 15:15:26 by lubenard          #+#    #+#             */
/*   Updated: 2019/08/17 18:14:53 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_tabchr(char **tab, int pattern)
{
	int i;

	i = 0;
	while (tab[i])
	{
		if (ft_strchri(tab[i++], pattern))
			return (1);
	}
	return (0);
}
