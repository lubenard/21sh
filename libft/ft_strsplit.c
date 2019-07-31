/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/16 08:59:56 by lubenard          #+#    #+#             */
/*   Updated: 2019/07/31 17:12:04 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

static int		countwords(char const *s, char c)
{
	size_t	compteur;
	size_t	i;

	i = 0;
	compteur = 0;
	while (i < ft_strlen(s))
	{
		if (i == 0 && s[i] != c)
			compteur++;
		if (s[i] == c && s[i + 1] != c && s[i + 1] != '\0')
			compteur++;
		i++;
	}
	return (compteur);
}

static int		countchar(char const *str, int i, char c)
{
	int nbrchar;

	nbrchar = 0;
	while (str[i])
	{
		if (str[i] && str[i] != c)
			nbrchar++;
		else
			return (nbrchar);
		i++;
	}
	return (nbrchar);
}

char			**ft_strsplit(char const *s, char c)
{
	char	**ret;
	int		j;
	int		i;
	int		k;
	int		nbr_words;

	j = 0;
	i = 0;
	nbr_words = countwords(s, c);
	printf("countchar vaut %d\n", countchar(s,i, c));
	if (!s)
		return (0);
	if (!(ret = (char **)malloc(sizeof(char *) * (nbr_words + 1))))
		return (0);
	while (s[i] == c)
		i++;
	while (j < nbr_words)
	{
		k = 0;
		printf("countchar vaut %d\n", countchar(s,i, c));
		if (!(ret[j] = ft_strnew(countchar(s, i, c))))
			return (0);
		while (s[i] && s[i] != c)
			ret[j][k++] = s[i++];
		i++;
		j++;
	}
	ret[j] = 0;
	return (ret);
}
