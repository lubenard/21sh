/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/12 14:01:27 by lubenard          #+#    #+#             */
/*   Updated: 2019/09/23 17:09:44 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh21.h>

int		ft_exit(t_hustru *big_struc, int nbr)
{
	free_after_exit(big_struc->lkd_env, big_struc->lkd_hist, big_struc->path);
	free(big_struc);
	reset_shell_attr(0);
	exit(nbr);
}

int		ft_atoi_exit(char *str)
{
	size_t	output;
	int		i;
	int		mult;

	output = 0;
	i = 0;
	mult = 1;
	if (str[i] == '+' || str[i] == '-')
	{
		mult = (str[i] == '-') ? -1 : 1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		output = output * 10 + str[i] - 48;
		i++;
	}
	if (output > INT_MAX || (int)output < INT_MIN)
		return (display_error("ymarsh: exit: integer is expected\n", NULL));
	free(str);
	return (output * mult);
}

int		parse_exit(t_hustru *big_struc, char **command)
{
	int		e;

	e = 0;
	if (command[2])
	{
		ft_putstr_fd("ymarsh: exit: Too many arguments\n", 2);
		return (ft_exit(big_struc, 255));
	}
	else
		return (ft_exit(big_struc, ft_atoi_exit(command[1])));
}

int		find_exit(t_hustru *big_struc, char **command)
{
	ft_putstr_fd("exit\n", 2);
	if (command[1])
		return (parse_exit(big_struc, command));
	return (ft_exit(big_struc, 0));
}
