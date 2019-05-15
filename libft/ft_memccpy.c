/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/09 16:14:18 by lubenard          #+#    #+#             */
/*   Updated: 2018/11/22 13:54:10 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *s1, const void *s2, int c, size_t n)
{
	int i;

	i = 0;
	while (i < (int)n)
	{
		((unsigned char *)s1)[i] = ((unsigned char *)s2)[i];
		if (((unsigned char *)s1)[i] == (unsigned char)c)
			return ((unsigned char *)s1 + i + 1);
		i++;
	}
	return (NULL);
}
