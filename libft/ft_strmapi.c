/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/15 15:35:54 by lubenard          #+#    #+#             */
/*   Updated: 2018/11/15 16:38:35 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	t;
	int		i;
	char	*str;

	i = 0;
	if (!s)
		return (0);
	if (!(str = (char *)malloc(sizeof(char) * ft_strlen(s) + 1)))
		return (0);
	while (s[i])
	{
		t = f(i, s[i]);
		str[i] = t;
		i++;
	}
	str[i] = '\0';
	return (str);
}
