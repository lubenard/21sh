/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlenu.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymarcill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/17 19:26:05 by ymarcill          #+#    #+#             */
/*   Updated: 2019/09/17 19:26:33 by ymarcill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh21.h>

int		ft_strlenu(char *str)
{
	int				i;
	int				y;
	unsigned char	*tmp;

	i = 0;
	y = 0;
	tmp = (unsigned char*)str;
	if (str)
	{
		while (tmp[i])
		{
			if (tmp[i] >> 7 == 0b1)
			{
				if (tmp[i] >> 5 == 0b00000110)
					y--;
				else if (tmp[i] >> 4 == 0b00001110)
					y = y - 2;
				else if (tmp[i] >> 3 == 0b00011110)
					y = y - 3;
			}
			i++;
			y++;
		}
	}
	return (y);
}
