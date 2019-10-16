/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/19 10:18:43 by lubenard          #+#    #+#             */
/*   Updated: 2019/10/16 14:31:51 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_realloc(char **str, int size)
{
	char	*rep;
	int		i;

	if (!str)
		return (NULL);
	i = ft_strlen(*str);
	if (!(rep = (char *)malloc(sizeof(char) * (i + size + 1))))
		return (NULL);
	ft_bzero(rep, i + size + 1);
	ft_strcpy(rep, *str);
	free(*str);
	*str = rep;
	return (rep);
}
