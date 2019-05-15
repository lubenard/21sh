/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/09 12:10:45 by lubenard          #+#    #+#             */
/*   Updated: 2018/11/21 15:56:54 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(char const *str, char const *to_find)
{
	int		i;
	int		j;

	i = 0;
	if (!str[0] && !to_find[0])
		return ((char *)str);
	if (!str[0] && to_find[0])
		return (0);
	while (str[i])
	{
		j = 0;
		while (str[i + j] == to_find[j] && to_find[j])
			j++;
		if (!to_find[j])
			return ((char *)str + i);
		i++;
	}
	if (!str[i] && !to_find[j])
		return (0);
	return (0);
}
