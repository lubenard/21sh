/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stricpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/28 09:23:24 by lubenard          #+#    #+#             */
/*   Updated: 2019/08/28 09:26:16 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_stricpy(char *dest, char *src, int start)
{
	int		i;

	i = 0;
	while (src[start])
		dest[i++] = src[start++];
	return (dest);
}
