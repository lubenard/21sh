/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 10:49:54 by lubenard          #+#    #+#             */
/*   Updated: 2019/05/13 13:53:42 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char		*ft_result(char *result, long int nbr, int n)
{
	if (n < 0)
		result[1] = nbr + '0';
	else
		result[0] = nbr + '0';
	return (result);
}

static int		ft_len(int n)
{
	long int	nbr;
	int			i;

	nbr = n;
	i = 0;
	if (nbr < 0)
		nbr = nbr * -1;
	while (nbr / 10 > 9)
	{
		i++;
		nbr = nbr / 10;
	}
	if (n < 0)
		return (i + 2);
	else
		return (i + 1);
}

char			*ft_itoa(int n)
{
	long int	nbr;
	int			neg;
	int			i;
	char		*result;

	nbr = n;
	neg = 0;
	i = 0;
	neg = (nbr < 0) ? -1 : 0;
	if (!(result = ft_strnew(ft_len(n) - neg)))
		return (NULL);
	if (nbr < 0)
	{
		nbr = nbr * -1;
		result[i] = '-';
		i++;
	}
	while ((ft_len(n) - i) > 0 && n != 0 && nbr > 9)
	{
		result[ft_len(n) - i - neg] = (nbr % 10) + '0';
		nbr = nbr / 10;
		i++;
	}
	return (ft_result(result, nbr, n));
}
