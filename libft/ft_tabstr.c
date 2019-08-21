/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tabstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/20 14:29:49 by lubenard          #+#    #+#             */
/*   Updated: 2019/08/21 17:01:04 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_tabstr(char **tab, char const *to_find)
{
	int		i;
	char	*ret;

	i = 0;
	while (tab[i])
	{
		if ((ret = ft_strstr(tab[i], to_find)) != 0)
			return (ret);
		i++;
	}
	return (0);
}
