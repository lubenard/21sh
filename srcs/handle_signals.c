/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_signals.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 14:21:03 by lubenard          #+#    #+#             */
/*   Updated: 2020/01/21 12:09:41 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh21.h>

/*
** Handle signal when inside a fork, during execution
*/

void	handle_signals_proc(int sig)
{
	if (sig == SIGINT)
		ft_putchar('\n');
}
