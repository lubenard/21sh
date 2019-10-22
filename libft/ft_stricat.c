/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stricat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/15 14:44:20 by lubenard          #+#    #+#             */
/*   Updated: 2019/10/15 14:51:01 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_stricat(char *dest, char *src, int start)
{
	int		i;
	int		e;

	i = 0;
	e = 0;
	while (dest[i])
		i++;
	while (src[start])
		dest[e + i++] = src[start++];
	dest[e + i] = '\0';
	return (dest);
}
