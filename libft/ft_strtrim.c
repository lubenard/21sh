/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/16 13:12:55 by lubenard          #+#    #+#             */
/*   Updated: 2018/11/19 14:59:52 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(const char *s)
{
	int		i;
	int		len;

	i = 0;
	if (!s)
		return (0);
	len = ft_strlen(s) - 1;
	while ((s[i] == '\t' || s[i] == ' ' || s[i] == '\n') && s[i] != '\0')
		i++;
	if (!s[i])
		return (ft_strdup(""));
	while ((s[len] == '\t' || s[len] == ' ' || s[len] == '\n') && len >= 0)
		len--;
	return (ft_strsub(s, i, len - i + 1));
}
