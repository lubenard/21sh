/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_builtins.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/15 17:03:58 by lubenard          #+#    #+#             */
/*   Updated: 2019/08/02 16:45:28 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh21.h>

char	*error_setenv(char *command, int i, int e)
{
	if (ft_strrchr(command, i, ' ') != NULL)
	{
		ft_putstr_fd("setenv: invalid syntax\n", 2);
		ft_putstr_fd("the correct syntax is t=1\n", 2);
		return (NULL);
	}
	return (ft_strsub(command, i, e));
}

int		print_shell_help(void)
{
	ft_putendl("Usage:");
	ft_putendl("-l     : Load history from .history file");
	ft_putendl("--help : Print this help");
	ft_putendl("\nExample: ./21sh -l");
	return (1);
}
