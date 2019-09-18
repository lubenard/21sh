/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymarcill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/18 11:22:02 by ymarcill          #+#    #+#             */
/*   Updated: 2019/09/18 11:22:48 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <input.h>

int		singleton(int comp)
{
	static pid_t save;

	if (comp != -1)
		save = comp;
	return (save);
}

void	signalhandler(int signal)
{
	pid_t tmp;

	tmp = singleton(-1);
	if (tmp)
		kill(tmp, signal);
	else
		ioctl(0, TIOCSTI, "\7");
}
