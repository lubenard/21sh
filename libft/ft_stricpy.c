/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stricpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 14:40:07 by lubenard          #+#    #+#             */
/*   Updated: 2019/10/09 14:40:20 by lubenard         ###   ########.fr       */
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
