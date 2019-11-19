/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term_mode.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymarcill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/20 16:48:08 by ymarcill          #+#    #+#             */
/*   Updated: 2019/11/19 04:30:40 by ymarcill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <input.h>
#include <term.h>
#include <stdio.h>

struct termios	term;

char	*copy_until(char *str, int i)
{
	char	*dst;
	int		j;

	j = 0;
	if (!(dst = malloc(sizeof(char) * i + 2)) || i >= ft_strlenu(str))
		return (str);
	while (j <= i)
	{
		dst[j] = str[j];
		j++;
	}
	dst[j] = '\0';
	return (dst);
}

/*
** term.c_lflag &= ~(ICANON | ECHO)
** Met le terminal en mode canonique
*/

int		set_none_canon_mode(int fd)
{	
	if (isatty(fd))
	{
		if (tcgetattr(fd, &term) == -1)
			return (-1);
		term.c_lflag &= ~(ICANON | ECHO);
		term.c_cc[VMIN] = 1;
		term.c_cc[VTIME] = 0;
		if (tcsetattr(fd, TCSADRAIN, &term) == -1)
			return (-1);
	}
	return (0);
}

/*
** old.c_lflag |= ICANON;
** Met le terminal en mode canonique
*/

int		reset_shell_attr(int fd)
{
	if (isatty(fd))
	{
		if (tcgetattr(fd, &term) == -1)
			return (-1);
		term.c_lflag |= ICANON;
		term.c_lflag |= ECHO;
		if (tcsetattr(fd, TCSADRAIN, &term) == -1)
			return (-1);
	}
	return (0);
}
