/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit_redir.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/16 08:59:56 by lubenard          #+#    #+#             */
/*   Updated: 2019/08/15 20:35:18 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh21.h>

static int		countwords(char const *s, char c)
{
	size_t	compteur;
	size_t	i;

	if (s == NULL)
		return (0);
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

int				countchar(char const *str, int j, char c)
{
	int nbrchar;

	nbrchar = 0;
	while (str[j])
	{
		if (str[j] && (str[j] != c || nbrchar == 0))
			nbrchar++;
		else
			return (nbrchar);
		j++;
	}
	return (nbrchar);
}

char			**ft_strsplit_redir(char const *s, char c)
{
	char	**ret;
	int		j;
	int		i;
	int		k;

	j = 0;
	i = 0;
	k = 0;
	if (!(ret = (char **)malloc(sizeof(char *) * (countwords(s, c) + 1)))
	|| countwords(s, c) == 0)
		return (0);
	while (j < countwords(s, c))
	{
		k = countchar(s, i, c);
		ret[j] = ft_strsub(s, i, k);
		if (s[i] == c)
			i++;
		while (s[i] && s[i] != c)
			i++;
		i++;
		j++;
	}
	ret[j] = 0;
	return (ret);
}
