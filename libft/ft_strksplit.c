/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strksplit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 17:46:05 by lubenard          #+#    #+#             */
/*   Updated: 2019/11/20 18:57:34 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		count_words(char *s, char c)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (s[i])
	{
		if (i == 0 && s[i] != c)
			j++;
		if (s[i] == c)
			j++;
		if (s[i] == c && s[i + 1] != c && s[i + 1] != '\0')
			j++;
		i++;
	}
	return (j);
}

static int		countchar(char *s, int i, char c)
{
	int		j;

	j = 0;
	if (s[i] == c)
		return (1);
	while (s[i] && s[i] != c)
	{
		i++;
		j++;
	}
	return (j);
}

static char		**malloc_main_array(char *s, char c)
{
	int		nbr_words;
	char	**ret;

	nbr_words = count_words(s, c);
	if (!(ret = malloc(sizeof(char *) * (nbr_words + 1))))
		return (NULL);
	return (ret);
}

char			**ft_strksplit(char *s, char c)
{
	char	**ret;
	int		k;
	int		i;
	int		m;

	m = 0;
	k = 0;
	i = 0;
	ret = malloc_main_array(s, c);
	while (k != count_words(s, c))
	{
		m = 0;
		if (!(ret[k] = ft_strnew(countchar(s, i, c))))
			return (NULL);
		if (s[i] == c)
			ret[k][m] = s[i++];
		else
		{
			while (s[i] && s[i] != c)
				ret[k][m++] = s[i++];
		}
		k++;
	}
	ret[k] = NULL;
	return (ret);
}
