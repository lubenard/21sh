/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <lubenard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/25 12:49:07 by lubenard          #+#    #+#             */
/*   Updated: 2018/12/06 17:41:28 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char				*ft_strndup(const char *s, size_t n)
{
	unsigned int	i;
	char			*cpy;

	if (!(cpy = (char*)malloc(sizeof(*cpy) * (n + 1))))
		return (NULL);
	i = 0;
	while (s[i] && i < n)
	{
		cpy[i] = s[i];
		i++;
	}
	cpy[i] = '\0';
	return (cpy);
}
