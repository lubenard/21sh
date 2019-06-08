/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/04 14:09:48 by lubenard          #+#    #+#             */
/*   Updated: 2019/06/08 13:59:09 by lubenard         ###   ########.fr       */
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
	ft_putstr("usage: env [-iv0] [--help]\n");
	ft_putstr("\t   [name=value ...] command\n");
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
	int		n;
	int		j;

	e = 0;
	i = 0;
	n = 0;
	j = 0;
	while (command[i])
	{
		if ((k = ft_strchri(command[i], '=')) && k != 1)
		{
			if (!j)
				j = i;
			e++;
		}
		i++;
	}
	return (e);
}

int		print_env_no_command(t_env *env, char **to_free, int flags, int *is_command)
{
	int i;
	t_env *tmp;

	i = 0;
	*is_command = 0;
	while (env)
	{
		if (ft_strcmp(env->env_line, ""))
		{
			ft_putstr(env->env_line);
			if (!(flags & PE_0))
				ft_putchar('\n');
		}
		env = env->next;
	}
	while (env)
	{
		tmp = env;
		env = env->next;
		free(tmp);
	}
	while (to_free[i])
		free(to_free[i++]);
	free(to_free);
	return (0);
}

void	fill_env(t_env **env, char **command, int i, t_env *tmp)
{
	t_env	*new_element;

	printf("Je suis sur %s\n", command[i]);
	printf("find_in_env return %s for %s\n", find_in_env(tmp, extract_first_env(command[i], 0)), extract_first_env(command[i], 0));
	if (find_in_env(tmp, extract_first_env(command[i], 0)))
	{
		printf("On remplace le maillon existant\n");
		while (tmp)
		{
			if (!ft_strcmp(extract_first_env(command[i], 0), extract_first_env(tmp->env_line, 0)))
			{
				printf("Je suis sur %s et je copie %s a sa place\n",tmp->env_line, command[i]);
				ft_strcpy(tmp->env_line, command[i]);
				break ;
			}
			tmp = tmp->next;
		}
	}
	else
	{
		printf("Pas de remplacement\n");
		ft_strcpy((*env)->env_line, command[i]);
		if (command[i + 1] && ft_strchr(command[i + 1], '=') && !find_in_env(tmp, ft_strdup(command[i + 1])))
		{
			new_element = new_maillon_env();
			(*env)->next = new_element;
			(*env)->next->prev = (*env);
			(*env) = new_element;
		}
	}
}

void	print_env_and_var(t_env *lkd_env, char **command, int flags)
{
	int i;
	int k;

	i = 0;
	print_basic_env(lkd_env, flags, 1);
	while (command[i] && !ft_strchr(command[i], '='))
		i++;
	while (command[i] && (k = ft_strchri(command[i], '=')) && k != 1)
	{
		ft_putstr(command[i++]);
		if (!(flags & PE_0))
			ft_putchar('\n');
	}
}

t_env	*parse_env(t_env *lkd_env, char **command, int flags, int *is_command)
{
	int		i;
	size_t	k;
	t_env	*env;
	t_env	*tmp;

	i = 0;
	if (flags & PE_I)
	{
		env = new_maillon_env();
		tmp = env;
		while (command[i] && !ft_strchr(command[i], '='))
			i++;
		while (command[i] && (k = ft_strchri(command[i], '=')) && k != 1)
		{
			fill_env(&env, command, i, tmp);
			i++;
		}
		printf("Command[%d] vaut %s\n",i ,command[i]);
		printf("K vaut %zu\n", k);
		if (!command[i])
			print_env_no_command(tmp, command, flags, is_command);
		return (tmp);
	}
	else
		print_env_and_var(lkd_env, command, flags);
	return (NULL);
}

int		launch_command_env(t_env *lkd_env, int flags, char **command)
{
	t_env	*env;
	int		is_command;

	is_command = 1;
	env = parse_env(lkd_env, command, flags, &is_command);
	printf("premier maillon vaut %s\n", env->env_line);
	printf("is_command vaut %d\n", is_command);
	return (0);
}

int		env_available_option(char *tab, int *flags)
{
	int i;

	while (*(++tab))
	{
		if (!(i = ft_strchri("iv0", tab[0])))
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
		print_basic_env(lkd_env, 0, 0);
		return (0);
	}
	else
		return (parsing_env(lkd_env, command));
}
