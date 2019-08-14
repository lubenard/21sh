/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term_mode.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymarcill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/20 16:48:08 by ymarcill          #+#    #+#             */
/*   Updated: 2019/08/14 13:13:53 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <input.h>

int set_none_canon_mode(int fd)
{
	struct  termios term;

	if (tcgetattr(fd, &term) == -1)
		return (-1);
	term.c_lflag &= ~(ICANON | ECHO | ISIG); // Met le terminal en mode canonique.
	term.c_cc[VMIN] = 1;
	term.c_cc[VTIME] = 0;
	if (tcsetattr(fd, TCSADRAIN, &term) == -1)
		return (-1);
	return (0);
}

int     reset_shell_attr(int fd)
{
	struct termios old;

	if (tcgetattr(fd, &old) == -1)
		return (-1);
	old.c_lflag |= ICANON; // Met le terminal en mode canonique.
	old.c_lflag |= ECHO;      
	old.c_lflag |= ISIG;// N'affiche pa ce qu'on ecrit.
	if (tcsetattr(fd, TCSADRAIN, &old) == -1)
		return (-1);
	return (0);
}

