/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/12 14:01:27 by lubenard          #+#    #+#             */
/*   Updated: 2019/06/13 21:41:21 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh21.h>

int		ft_exit(int nbr, t_hustru *big_struc)
{
	free_after_exit(big_struc->lkd_env, big_struc->lkd_hist, big_struc->path);
	free(big_struc);
	printf("nbr vaut %d\n", nbr);
	return (nbr);
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
	{
		ft_putstr_fd("ymarsh: exit: integer is expected\n", 2);
		return (255);
	}
	free(str);
	return (output * mult);
}

int		check_exit_val(char *str, int i, int e)
{
	while (str[i + e] && str[i + e] != ' ')
	{
		if (!ft_isdigit(str[i + e]))
		{
			ft_putstr_fd("ymarsh: exit: integer is expected\n", 2);
			return (-1);
		}
		e++;
	}
	return (0);
}

int		parse_exit(char *command, int i, t_hustru *big_struc)
{
	char	*ret_val;
	int		e;

	e = 0;
	while (command[i] == ' ')
		i++;
	ft_putstr_fd("exit\n", 2);
	if (!command[i])
		return (ft_exit(0, big_struc));
	else
	{
		if (command[i + e] == '-')
			e++;
		if (check_exit_val(command, i, e) == -1)
			return (ft_exit(255, big_struc));
		while (ft_isdigit(command[i + e]))
			e++;
		ret_val = ft_strsub(command, i, e);
		if (command[i + e])
			ft_putstr_fd("ymarsh: exit: Too many arguments\n", 2);
		else
			return (ft_exit(ft_atoi_exit(ret_val), big_struc));
	}
	return (0);
}

int		find_exit(char *command, t_hustru *big_struc)
{
	char	*ret;
	int		i;

	i = 0;
	while (ft_isalnum(command[i]))
		i++;
	ret = ft_strsub(command, 0, i);
	if (ft_strequ(ret, "exit"))
	{
		free(ret);
		return (parse_exit(command, i, big_struc));
	}
	free(ret);
	return (0);
}
