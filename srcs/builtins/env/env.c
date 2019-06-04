/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/04 14:09:48 by lubenard          #+#    #+#             */
/*   Updated: 2019/06/04 22:53:12 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../sh21.h"

int		print_error_env(char option, int mode)
{
	if (mode == 0)
	{
		ft_putstr("env : illegal option -- ");
		ft_putchar(option);
		ft_putchar('\n');
	}
	ft_putstr("usage: env [-iv] [-P utilpath] [--help]\n");
	ft_putstr("\t   [name=value ...] command\n");
	return (0);
}

int		print_basic_env(t_env *lkd_env)
{
	while (lkd_env)
	{
		if (ft_strcmp(lkd_env->env_line, "")
		&& !lkd_env->prev && !lkd_env->next)
		{
			ft_putstr(lkd_env->env_line);
			ft_putchar('\n');
		}
		lkd_env = lkd_env->next;
	}
	return (0);
}

void	print_verbose_env(int flags, char *argv, int mode)
{
	if (flags & PE_I)
		ft_putstr("#env clearing environ\n");
	if (mode == 0)
	{
		ft_putstr("#env\targv[0]= '");
		ft_putstr(argv);
		ft_putendl("'");
	}
}

int		count_elem_env(char **command)
{
	int		i;
	int		e;
	size_t	k;

	e = 0;
	i = 0;
	while (command[i])
	{
		if ((k = ft_strchri(command[i], '=')) && k != 1)
			e++;
		i++;
	}
	return (e);
}

int		print_env_no_command(char **tab, int j)
{
	while (tab[j])
		ft_putendl(tab[j++]);
	return (0);
}

char	**parse_env(char **command, int flags)
{
	int		i;
	char	**tab;
	size_t	k;
	int		j;

	printf("J'ai %d elems\n", count_elem_env(command));
	if (!(tab = (char **)malloc(sizeof(char *) * count_elem_env(command))))
		return (NULL);
	i = 0;
	if (flags & PE_I)
	{
		while (command[i] && !ft_strchr(command[i], '='))
			i++;
		j = i;
		while (command[i] && (k = ft_strchri(command[i], '=')) && k != 1)
		{
			printf("command[%d] = %s\n", i, command[i]);
			i++;
		}
		printf("je check %s\n", command[i]);
		if (!command[i])
			print_env_no_command(command, j);
	}
	return (0);
}

int		launch_command_env(t_env *lkd_env, int flags, char **command)
{
	char **env;

	if (!(env = parse_env(command, flags)))
		return (print_basic_env(lkd_env));
	return (0);
}

int		env_available_option(char *tab, int *flags)
{
	int i;

	while (*(++tab))
	{
		if (!(i = ft_strchri("iPv", tab[0])))
		{
			print_error_env(tab[0], 0);
			return (0);
		}
		printf("I vaut %d\n", i);
		*flags |= (1 << (i - 1));
	}
	return (i);
}

int		parsing_env(t_env *lkd_env, char *command)
{
	int		flags;
	int		i;
	char	**tab;

	flags = 0;
	i = 1;
	if (ft_strstr(command, "--help"))
		return (print_error_env('c', 1));
	tab = ft_strsplit(command, ' ');
	while (tab[i] && tab[i][0] == '-' && tab[i][1])
	{
		if (tab[i][1] == '-' && !tab[i][2])
			return (1 + i);
		if (!env_available_option(tab[i], &flags))
			return (0);
		i++;
	}
	launch_command_env(lkd_env, flags, tab);
	return (0);
}

int		print_env(t_env *lkd_env, char *command)
{
	if (!ft_strcmp(command, "env"))
	{
		print_basic_env(lkd_env);
		return (0);
	}
	else
		return (parsing_env(lkd_env, command));
}
