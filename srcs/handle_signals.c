/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_signals.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 14:21:03 by lubenard          #+#    #+#             */
/*   Updated: 2019/10/22 14:31:00 by ymarcill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh21.h>
#include <input.h>

/*
** Handle signal when inside a fork, during execution
*/

void	handle_signals_proc(int sig)
{
	if (sig == SIGINT)
	{
		ioctl(0, TIOCSTI, "\7");
		ft_putchar('\b');
		ft_putchar(127);
		ft_putchar('\b');
		ft_putchar('\b');
		ft_putchar(127);
		ft_putchar('\b');
		ft_putstr("\n");
	}
}
