/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnncpy.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <lubenard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 13:48:27 by lubenard          #+#    #+#             */
/*   Updated: 2019/05/15 12:45:51 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

char	*ft_strnncpy(char *dest, char const *src, unsigned int i,
	unsigned int n)
{
	int k;

	k = 0;
	while (src[i] && i < n)
	{
		dest[k] = src[i];
		i++;
		k++;
	}
	while (i < n)
	{
		dest[k++] = '\0';
		k++;
		i++;
	}
	return (dest);
}
