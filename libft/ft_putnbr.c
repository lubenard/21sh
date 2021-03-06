/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 09:30:30 by lubenard          #+#    #+#             */
/*   Updated: 2018/11/13 11:11:09 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr(int n)
{
	if (n >= 2147483647)
	{
		n = 147483647;
		ft_putchar('2');
	}
	else if (n < 0)
	{
		ft_putchar('-');
		if (n <= -2147483648)
		{
			n = 147483648;
			ft_putchar('2');
		}
		else
			n *= -1;
	}
	if (n > 9)
	{
		ft_putnbr(n / 10);
		ft_putnbr(n % 10);
	}
	else
		ft_putchar(n + '0');
}
