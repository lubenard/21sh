/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/11 23:58:21 by lubenard          #+#    #+#             */
/*   Updated: 2018/11/14 17:37:01 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_memcmp(void const *s1, void const *s2, size_t n)
{
	int					i;
	unsigned char const	*t1;
	unsigned char const	*t2;

	t1 = s1;
	t2 = s2;
	i = 0;
	if (n == 0)
		return (0);
	while (i != (int)n - 1 && t1[i] == t2[i])
		i++;
	return ((unsigned char)t1[i] - (unsigned char)t2[i]);
}
