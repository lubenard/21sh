/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/02 14:45:42 by lubenard          #+#    #+#             */
/*   Updated: 2019/08/27 18:50:06 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh21.h>

void	error_echo(char user[33])
{
	ft_putstr_fd("ymarsh : no such user or directory: ", 2);
	ft_putendl_fd(user, 2);
}

int		handle_tilde2(t_env *lkd_env)
{
	char *str;

	str = find_in_env(lkd_env, ft_strdup("HOME"));
	ft_putstr(str);
	free(str);
	return (0);
}
