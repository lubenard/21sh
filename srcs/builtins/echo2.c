/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/14 13:53:33 by lubenard          #+#    #+#             */
/*   Updated: 2019/09/14 14:28:22 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh21.h>

void	handle_echo_options(char option)
{
	if (option == 'a')
		ft_putchar('\a');
	else if (option == 'b')
		ft_putchar('\b');
	else if (option == 'f')
		ft_putchar('\f');
	else if (option == 'n')
		ft_putchar('\n');
	else if (option == 'r')
		ft_putchar('\r');
	else if (option == 't')
		ft_putchar('\t');
	else if (option == 'v')
		ft_putchar('\v');
}
