/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_builtins.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/15 17:03:58 by lubenard          #+#    #+#             */
/*   Updated: 2019/09/23 16:24:06 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh21.h>

int		error_setenv(int i)
{
	if (i == 1)
		ft_putstr_fd("un", 2);
	ft_putstr_fd("setenv: invalid syntax\n", 2);
	ft_putstr_fd("The correct syntax is var=value\n", 2);
	return (1);
}

int		print_error_redirect(char *code)
{
	int i;

	i = 0;
	ft_putstr_fd("ymarsh: parse error near ", 2);
	ft_putendl_fd(code, 2);
	return (1);
}

int		display_error(char *error, char *command)
{
	if (error)
		ft_putstr_fd(error, 2);
	if (command)
		ft_putendl_fd(command, 2);
	return (1);
}

int		print_shell_help(void)
{
	ft_putendl("Usage:");
	ft_putendl("-l     : Load history from .history file");
	ft_putendl("--help : Print this help");
	ft_putendl("\nExample: ./21sh -l");
	return (1);
}
