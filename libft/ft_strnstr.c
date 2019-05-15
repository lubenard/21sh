/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/09 13:15:16 by lubenard          #+#    #+#             */
/*   Updated: 2018/11/21 15:52:43 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(char const *s1, char const *s2, size_t e)
{
	int		i;
	int		j;

	i = 0;
	if (!s1[0] && !s2[0])
		return ((char *)s1);
	if (!s1[0] && s2[0])
		return (0);
	while (s1[i] && i < (int)e)
	{
		j = 0;
		while (s1[i + j] == s2[j] && s2[j] && (i + j < (int)e))
			j++;
		if (!s2[j])
			return ((char *)s1 + i);
		i++;
	}
	return (0);
}
