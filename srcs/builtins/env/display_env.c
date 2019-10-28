/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/22 13:39:46 by lubenard          #+#    #+#             */
/*   Updated: 2019/10/28 15:13:39 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <env.h>

void	print_verbose_env2(char **argv, int i)
{
	while (argv[i])
	{
		ft_putstr("#env\targv[");
		ft_putnbr(i);
		ft_putstr("]= '");
		ft_putstr(argv[i++]);
		ft_putendl("'");
	}
}

void	print_verbose_env(t_env *env, char **argv, int mode)
{
	int i;

	i = 0;
	if (mode == 0)
		ft_putstr("#env clearing environ\n");
	else if (mode == 1)
	{
		while (env)
		{
			if (ft_strcmp(env->env_line, ""))
			{
				ft_putstr("#env setenv:\t");
				ft_putendl(env->env_line);
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
		ft_putstr("env : illegal option -- ");
		ft_putchar(option);
		ft_putchar('\n');
	}
	ft_putstr("usage: env [--help] [-iv0]\n");
	ft_putstr("\t   [name=value ...] [command]\n");
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
			ft_putstr(lkd_env->env_line);
			if (mode == 1 && !(flags & PE_0))
				ft_putchar('\n');
			else if (mode == 0)
				ft_putchar('\n');
		}
		lkd_env = lkd_env->next;
	}
	return (0);
}

t_env	*print_env_and_var(t_env *lkd_env, t_env *env,
	int flags, int *is_command)
{
	if (flags & PE_V)
		print_verbose_env(env, NULL, 1);
	*is_command = 0;
	print_basic_env(lkd_env, flags, 1);
	print_basic_env(env, flags, 1);
	free_env(env);
	return (NULL);
}
