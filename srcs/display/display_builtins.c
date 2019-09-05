/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_builtins.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/15 17:03:58 by lubenard          #+#    #+#             */
/*   Updated: 2019/09/05 17:50:53 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh21.h>

char	*error_setenv(char *command, int i, int e)
{
	if (ft_strrchr(command, i, ' ') != NULL)
	{
		ft_putstr_fd("setenv: invalid syntax\n", 2);
		ft_putstr_fd("the correct syntax is t=1\n", 2);
		eturn (NULL);
	}
	return (ft_strsub(command, i, e));
}

int		print_error_redirect(char **tab, char *code)
{
	int i;

	i = 0;
	ft_putstr_fd("ymarsh: parse error near ", 2);
	ft_putendl_fd(code, 2);
	ft_deltab(tab);
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
