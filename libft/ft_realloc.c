/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/19 10:18:43 by lubenard          #+#    #+#             */
/*   Updated: 2018/11/23 10:56:12 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_realloc(char *str, int size)
{
	char	*rep;
	int		i;

	i = ft_strlen(str);
	if (!(rep = (char*)malloc(sizeof(*rep) * (size + ft_strlen(str)))))
		return (NULL);
	while (++i < size)
		rep[i] = 0;
	i = 0;
	while (str[i])
	{
		rep[i] = str[i];
		++i;
	}
	free(str);
	return (rep);
}
