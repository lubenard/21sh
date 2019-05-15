/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/12 08:29:35 by lubenard          #+#    #+#             */
/*   Updated: 2018/11/13 21:31:54 by luca             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnew(size_t n)
{
	char	*dest;

	if (!(dest = (char *)malloc(sizeof(char) * n + 1)))
		return (NULL);
	ft_bzero(dest, sizeof(char) * n + 1);
	return (dest);
}
