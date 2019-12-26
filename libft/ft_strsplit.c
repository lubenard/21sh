/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/16 08:59:56 by lubenard          #+#    #+#             */
/*   Updated: 2019/12/26 13:55:29 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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

static int		return_i(char const *str, int i, char c)
{
	while (str[i] == c)
		i++;
	return (i);
}

static int		countchar(char const *str, int i, char c)
{
	int nbrchar;

	nbrchar = 0;
	i = return_i(str, i, c);
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
	if (!s || !(ret = (char **)malloc(sizeof(char *) * (nbr_words + 1))))
		return (0);
	while (j < nbr_words)
	{
		i = return_i(s, i, c);
		k = 0;
		if (!(ret[j] = ft_strnew(countchar(s, i, c) + 1)))
			return (0);
		while (s[i] && s[i] != c)
			ret[j][k++] = s[i++];
		j++;
	}
	ret[j] = NULL;
	return (ret);
}
