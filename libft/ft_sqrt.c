/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sqrt.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/06 09:05:17 by lubenard          #+#    #+#             */
/*   Updated: 2018/11/06 09:05:21 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		ft_sqrt(int nb)
{
	int rac_carre;

	rac_carre = 0;
	if (nb <= 0)
		return (0);
	while (rac_carre * rac_carre != nb)
	{
		if (rac_carre > nb / 2)
			return (0);
		rac_carre++;
	}
	if (nb / rac_carre == rac_carre)
		return (rac_carre);
	return (0);
}
