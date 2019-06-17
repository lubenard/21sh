/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoinnf.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymarcill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/08 21:22:01 by ymarcill          #+#    #+#             */
/*   Updated: 2018/05/15 03:57:54 by ymarcill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoinnf(char const *s1, char const *s2)
{
	char	*str;
	int		x;
	char	*tmp;

	if (!s1 || !(s2))
	{
		free((void*)s1);
		return (NULL);
	}
	x = ft_strlen(s2) + ft_strlen(s1);
	if (!(str = ft_strnew(x + 1)))
	{
		free((void*)s1);
		return (NULL);
	}
	tmp = str;
	tmp = ft_strcpy(tmp, s1);
	str = ft_strcat(tmp, s2);
	return (str);
}
