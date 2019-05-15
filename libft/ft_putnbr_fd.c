/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 09:30:30 by lubenard          #+#    #+#             */
/*   Updated: 2018/11/13 11:12:25 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	if (n >= 2147483647)
	{
		n = 147483647;
		ft_putchar_fd('2', fd);
	}
	else if (n < 0)
	{
		ft_putchar_fd('-', fd);
		if (n <= -2147483648)
		{
			n = 147483648;
			ft_putchar_fd('2', fd);
		}
		else
			n *= -1;
	}
	if (n > 9)
	{
		ft_putnbr_fd(n / 10, fd);
		ft_putnbr_fd(n % 10, fd);
	}
	else
		ft_putchar_fd(n + '0', fd);
}
