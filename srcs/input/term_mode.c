/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term_mode.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymarcill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/20 16:48:08 by ymarcill          #+#    #+#             */
/*   Updated: 2019/09/19 12:52:26 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <input.h>

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
	struct termios term;

	if (tcgetattr(fd, &term) == -1)
		return (-1);
	term.c_lflag &= ~(ICANON | ECHO);
	term.c_cc[VMIN] = 1;
	term.c_cc[VTIME] = 0;
	if (tcsetattr(fd, TCSADRAIN, &term) == -1)
		return (-1);
	return (0);
}

/*
** old.c_lflag |= ICANON;
** Met le terminal en mode canonique
*/

int		reset_shell_attr(int fd)
{
	struct termios old;

	if (tcgetattr(fd, &old) == -1)
		return (-1);
	old.c_lflag |= ICANON;
	old.c_lflag |= ECHO;
	if (tcsetattr(fd, TCSADRAIN, &old) == -1)
		return (-1);
	//ft_putchar_fd('\n', 0);
	return (0);
}
