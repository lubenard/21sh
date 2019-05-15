/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/09 16:51:03 by lubenard          #+#    #+#             */
/*   Updated: 2018/11/15 11:19:38 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		*ft_memmove(void *s1, void const *s2, size_t n)
{
	if ((unsigned char *)s2 < (unsigned char *)s1)
	{
		n--;
		while (n + 1 > 0)
		{
			((unsigned char *)s1)[n] = ((unsigned char *)s2)[n];
			n--;
		}
	}
	else
		ft_memcpy(s1, s2, n);
	return (s1);
}
