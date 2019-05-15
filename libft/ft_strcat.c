/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 15:58:14 by lubenard          #+#    #+#             */
/*   Updated: 2018/11/13 15:09:56 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcat(char *dest, char const *src)
{
	int i;
	int e;

	i = 0;
	e = 0;
	while (dest[i])
		i++;
	while (src[e])
	{
		dest[i + e] = src[e];
		e++;
	}
	dest[i + e] = '\0';
	return (dest);
}
