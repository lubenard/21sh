/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_conststrjoin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/15 17:04:12 by lubenard          #+#    #+#             */
/*   Updated: 2019/04/30 23:33:34 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

const char	*ft_conststrjoin(char const *s1, char const *s2)
{
	char	*ret;
	int		i;
	int		e;

	if (!s1 || !s2)
		return (0);
	i = 0;
	e = 0;
	if (!(ret = (char *)malloc(sizeof(char) * (ft_strlen(s1) + \
						ft_strlen(s2)) + 1)))
		return (0);
	while (s1[i])
	{
		ret[i] = s1[i];
		i++;
	}
	while (s2[e])
	{
		ret[i + e] = s2[e];
		e++;
	}
	ret[i + e] = '\0';
	return ((const char *)ret);
}
