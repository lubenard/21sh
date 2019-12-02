/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/22 13:39:46 by lubenard          #+#    #+#             */
/*   Updated: 2019/12/02 22:24:32 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <env.h>

void	print_verbose_env2(char **argv, int i)
{
	while (argv[i])
	{
		ft_putstr_fd("#env\targv[", 1);
		ft_putnbr(i);
		ft_putstr_fd("]= '", 1);
		ft_putstr_fd(argv[i++], 1);
		ft_putendl_fd("'", 1);
	}
}

void	print_verbose_env(t_env *env, char **argv, int mode)
{
	int i;

	i = 0;
	if (mode == 0)
		ft_putstr_fd("#env clearing environ\n", 1);
	else if (mode == 1)
	{
		while (env)
		{
			if (ft_strcmp(env->env_line, ""))
			{
				ft_putstr_fd("#env setenv:\t", 1);
				ft_putendl_fd(env->env_line, 1);
			}
			env = env->next;
		}
	}
	else if (mode == 2)
		print_verbose_env2(argv, i);
}

int		print_error_env(char option, int mode)
{
	if (mode == 0)
	{
		ft_putstr_fd("env : illegal option -- ", 2);
		ft_putchar_fd(option, 2);
		ft_putchar_fd('\n', 2);
	}
	ft_putstr_fd("usage: env [--help] [-iv0]\n", 2);
	ft_putstr_fd("\t   [name=value ...] [command]\n", 2);
	if (mode == 0)
		return (1);
	return (0);
}

int		print_basic_env(t_env *lkd_env, int flags, int mode)
{
	while (lkd_env)
	{
		if (ft_strcmp(lkd_env->env_line, ""))
		{
			ft_putstr_fd(lkd_env->env_line, 1);
			if (mode == 1 && !(flags & PE_0))
				ft_putchar_fd('\n', 1);
			else if (mode == 0)
				ft_putchar_fd('\n', 1);
		}
		lkd_env = lkd_env->next;
	}
	return (0);
}
