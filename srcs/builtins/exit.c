/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/12 14:01:27 by lubenard          #+#    #+#             */
/*   Updated: 2019/06/12 16:47:15 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh21.h>

int		ft_exit(int nbr)
{
	printf("nbr vaut %d\n", nbr);
	if (nbr > INT_MIN && nbr < INT_MAX)
		return (nbr);
	else
	{
		ft_putstr_fd("exit: error: integer is expected\n", 2);
		return (255);
	}

}

int		ft_atoi_exit(char *str, int *err)
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
		if (mult == 1 && output > MAX_INT64)
		{
			*err = 1;
			return (-1);
		}
		else if (mult == -1 && output > (size_t)(MAX_INT64) + 1)
			return (0);
		i++;
	}
	return (output * mult);
}

int		parse_exit(char *command)
{
	int		i;
	char	*ret_val;
	int		e;
	int		error;

	i = 0;
	e = 0;
	error = 0;
	while (command[i] && (ft_isalpha(command[i]) || command[i] == ' '))
		i++;
	ft_putstr_fd("exit\n", 2);
	printf("Je suis sur |%c|\n", command[i]);
	if (!command[i])
		ft_exit(0);
	else
	{
		while (ft_isdigit(command[i + e]))
			e++;
		ret_val = ft_strsub(command, i, e);
		if (command[i + e])
			ft_putstr_fd("exit: error: Too many arguments\n", 2);
		else
		{
			i = ft_atoi_exit(ret_val, &error);
			ft_exit(0);
		}
	}
}

int		find_exit(char *command)
{
	char	*ret;
	int		i;

	i = 0;
	while (ft_isalpha(command[i]))
		i++;
	ret = ft_strsub(command, 0, i);
	printf("Je rentre la et ret vaut |%s|\n", ret);
	if (ft_strequ(ret, "exit"))
		return (parse_exit(command));
	free(ret);
}

