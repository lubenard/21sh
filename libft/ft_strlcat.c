/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 16:33:02 by lubenard          #+#    #+#             */
/*   Updated: 2018/11/12 17:06:43 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, char const *src, size_t n)
{
	unsigned int i;
	unsigned int buff;
	unsigned int srclen;

	buff = ft_strlen(dest);
	i = 0;
	srclen = 0;
	while (src[i] && buff + i + 1 < n)
	{
		dest[buff + i] = src[i];
		i++;
	}
	dest[buff + i] = '\0';
	srclen = ft_strlen(src);
	if (n < buff)
		return (srclen + n);
	return (buff + srclen);
}
