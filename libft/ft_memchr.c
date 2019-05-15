/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/10 23:41:16 by lubenard          #+#    #+#             */
/*   Updated: 2018/11/19 15:31:23 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(void const *s, int c, size_t n)
{
	int		i;
	char	*t;

	t = (char *)s;
	i = 0;
	while (i < (int)n)
	{
		if ((char)c == *t)
			return (t);
		t++;
		i++;
	}
	return (NULL);
}
