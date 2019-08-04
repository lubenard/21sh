/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_signals.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 14:21:03 by lubenard          #+#    #+#             */
/*   Updated: 2019/08/04 12:41:40 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh21.h>

void	handle_signals_proc(int sig)
{
	extern pid_t g_pid;

	if (sig == SIGINT)
		ft_putstr("\n");
}

void	handle_signals(int sig)
{
	extern char *g_curr_dir;
	extern char *g_username;

	printf("Je suis appele\n");
	if (sig == SIGINT)
	{
		ft_putstr("\n");
		display_prompt(g_username, g_curr_dir);
	}
}
