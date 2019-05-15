/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 15:48:08 by lubenard          #+#    #+#             */
/*   Updated: 2018/11/21 12:41:16 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_atoi(char const *str)
{
	size_t	output;
	int		i;
	int		mult;

	output = 0;
	i = 0;
	mult = 1;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\v' \
			|| str[i] == '\n' || str[i] == '\r' || str[i] == '\f')
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		mult = (str[i] == '-') ? -1 : 1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		output = output * 10 + str[i] - 48;
		if (mult == 1 && output > MAX_INT64)
			return (-1);
		else if (mult == -1 && output > (size_t)(MAX_INT64) + 1)
			return (0);
		i++;
	}
	return (output * mult);
}
