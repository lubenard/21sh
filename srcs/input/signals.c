/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymarcill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/18 11:22:02 by ymarcill          #+#    #+#             */
/*   Updated: 2020/01/21 12:06:10 by lubenard         ###   ########.fr       */
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

void	signalhandler(int sig)
{
	pid_t tmp;

	if (sig == SIGINT)
	{
		tmp = singleton(-1);
		if (tmp)
			kill(tmp, sig);
		else
			ioctl(0, TIOCSTI, "\7");
		g_big_struc->last_ret = 130;
	}
}
