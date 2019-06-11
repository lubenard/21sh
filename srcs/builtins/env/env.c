/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/04 14:09:48 by lubenard          #+#    #+#             */
/*   Updated: 2019/06/11 08:27:50 by lubenard         ###   ########.fr       */
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

void	free_env(t_env *env, char **to_free)
{
	t_env	*tmp;
	int		i;

	i = 0;
	while (env)
	{
		tmp = env;
		env = env->next;
		free(tmp);
	}
	if (to_free != NULL)
	{
		while (to_free[i])
			free(to_free[i++]);
	}
	free(to_free);
}

t_env	*print_env_no_command(t_env *env, char **to_free,
	int flags, int *is_command)
{
	t_env *tmp;

	tmp = env;
	*is_command = 0;
	if (flags & PE_V && flags & PE_I)
		print_verbose_env(env, NULL, 1);
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
	free_env(tmp, to_free);
	return (NULL);
}

void	fill_env(t_env **env, char **command, int i, t_env *tmp)
{
	t_env	*new_element;
	char	*first_env;
	char	*first_env2;
	char	*fie;

	if ((fie = find_in_env(tmp, extract_first_env(command[i], 0))))
	{
		while (tmp)
		{
			first_env = extract_first_env(command[i], 0);
			first_env2 = extract_first_env(tmp->env_line, 0);
			if (!ft_strcmp(first_env, first_env2))
			{
				ft_strcpy(tmp->env_line, command[i]);
				free(first_env);
				free(first_env2);
				break ;
			}
			free(first_env);
			free(first_env2);
			tmp = tmp->next;
		}
	}
	else
	{
		ft_strcpy((*env)->env_line, command[i]);
		if (command[i + 1] && ft_strchr(command[i + 1], '=')
			&& !find_in_env(tmp, ft_strdup(command[i + 1])))
		{
			new_element = new_maillon_env();
			(*env)->next = new_element;
			(*env)->next->prev = (*env);
			(*env) = new_element;
		}
	}
	free(fie);
}

t_env	*print_env_and_var(t_env *lkd_env, t_env *env,
	int flags, int *is_command)
{
	if (flags & PE_V)
		print_verbose_env(env, NULL, 1);
	*is_command = 0;
	print_basic_env(lkd_env, flags, 1);
	print_basic_env(env, flags, 1);
	free_env(env, NULL);
	return (NULL);
}

t_env	*parse_env(t_env *lkd_env, char **command, int flags, int *is_command)
{
	int		i;
	size_t	k;
	t_env	*env;
	t_env	*tmp;

	i = 1;
	env = new_maillon_env();
	tmp = env;
	while (command[i] && ft_strchr(command[i], '-'))
		i++;
	while (command[i] && (k = ft_strchri(command[i], '=')) && k != 1)
		fill_env(&env, command, i++, tmp);
	if (!command[i] && flags & PE_I)
		return (print_env_no_command(tmp, command, flags, is_command));
	else if (!(flags & PE_I) && !command[i])
	{
		free_env(NULL, command);
		return (print_env_and_var(lkd_env, tmp, flags, is_command));
	}
	if (tmp->env_line[0] != '\0')
		return (tmp);
	free(env);
	return (NULL);
}

char	**compact_argv_env(char **command, int i)
{
	int		nbr_elem;
	char	**argv;
	int		k;

	nbr_elem = i;
	k = 0;
	while (command[i])
		i++;
	if (!(argv = (char **)malloc(sizeof(char *) * ((i - nbr_elem) + 1))))
		return (NULL);
	while (command[nbr_elem])
	{
		argv[k] = ft_strdup(command[nbr_elem]);
		nbr_elem++;
		k++;
	}
	argv[k] = NULL;
	return (argv);
}

int		exec_default_env(t_env *lkd_env, char **command, char **path, int flags)
{
	int		i;
	char	*right_path;
	char	*exec_path;
	char	**argv;
	char	**tab_env;

	i = 1;
	while (command[i][0] == '-' || ft_strchr(command[i], '='))
		i++;
	right_path = find_path(path, command[i]);
	if (flags & PE_V)
	{
		print_verbose_env(lkd_env, NULL, 1);
		if (right_path != NULL)
		{
			ft_putstr("#env executing: ");
			ft_putendl(command[i]);
		}
	}
	argv = compact_argv_env(command, i);
	if (flags & PE_V)
		print_verbose_env(NULL, argv, 2);
	if (right_path == NULL)
	{
		ft_putstr("No file found with the following name: ");
		ft_putendl(command[i]);
		free_env(lkd_env, command);
		return (1);
	}
	tab_env = compact_env(lkd_env);
	exec_path = ft_strjoin(right_path, command[i]);
	exec_command_gen(exec_path, argv, tab_env);
	free(right_path);
	free_env(NULL, command);
	return (0);
}

int		exec_file_env(t_env *env, char **command, char **path, int flags)
{
	int		i;
	char	*right_path;
	char	*exec_path;
	char	**argv;
	char	**tab_env;

	i = 1;
	while (command[i][0] == '-' || ft_strchr(command[i], '='))
		i++;
	right_path = find_path(path, command[i]);
	if (flags & PE_V)
	{
		print_verbose_env(env, NULL, 1);
		if (right_path != NULL)
		{
			ft_putstr("#env executing: ");
			ft_putendl(command[i]);
		}
	}
	argv = compact_argv_env(command, i);
	if (flags & PE_V)
		print_verbose_env(NULL, argv, 2);
	if (right_path == NULL)
	{
		ft_putstr("No file found with the following name: ");
		ft_putendl(command[i]);
		free_env(env, command);
		return (1);
	}
	tab_env = compact_env(env);
	exec_path = ft_strjoin(right_path, command[i]);
	exec_command_gen(exec_path, argv, tab_env);
	free(right_path);
	free_env(env, command);
	return (0);
}

int		launch_command_env(t_env *lkd_env, int flags,
	char **command, char **path)
{
	t_env	*env;
	int		is_command;
	t_env	*tmp;

	is_command = 1;
	env = parse_env(lkd_env, command, flags, &is_command);
	if (is_command == 1 && flags & PE_I)
		exec_file_env(env, command, path, flags);
	else
	{
		tmp = lkd_env;
		while (lkd_env->next)
			lkd_env = lkd_env->next;
		lkd_env->next = env;
		exec_default_env(tmp, command, path, flags);
	}
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
		*flags |= (1 << (i - 1));
	}
	if (*flags & PE_V && *flags & PE_I)
		print_verbose_env(NULL, NULL, 0);
	return (i);
}

int		parsing_env(t_env *lkd_env, char *command, char **path)
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
	launch_command_env(lkd_env, flags, tab, path);
	return (0);
}

int		print_env(t_env *lkd_env, char *command, char **path)
{
	if (!ft_strcmp(command, "env"))
	{
		print_basic_env(lkd_env, 0, 0);
		return (0);
	}
	else
		return (parsing_env(lkd_env, command, path));
}
