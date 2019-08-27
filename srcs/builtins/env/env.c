/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/04 14:09:48 by lubenard          #+#    #+#             */
/*   Updated: 2019/08/27 17:11:32 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <env.h>

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

void	fill_env(t_env **env, char **command, int i, t_env *tmp)
{
	t_env	*new_element;
	char	*first_env;
	char	*first_env2;
	char	*fie;

	if ((fie = find_in_env(tmp, extract_first(command[i], '='))))
	{
		while (tmp)
		{
			first_env = extract_first(command[i], '=');
			first_env2 = extract_first(tmp->env_line, '=');
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

void	verbose(t_env *env, char *right_path, char *command)
{
	print_verbose_env(env, NULL, 1);
	if (right_path != NULL)
	{
		ft_putstr("#env executing: ");
		ft_putendl(command);
	}
}

char	*exec_file_env(t_env *env, char **command,
	t_hustru *big_struc, int flags)
{
	char	**tab_env;
	char	*right_path;
	char	**argv;
	int		i;

	i = 1;
	while (command[i][0] == '-' || ft_strchr(command[i], '='))
		i++;
	right_path = find_path(big_struc->path, command[i]);
	if (flags & PE_V)
		verbose(env, right_path, command[i]);
	argv = compact_argv_env(command, i);
	if (flags & PE_V)
		print_verbose_env(NULL, argv, 2);
	if (right_path == NULL)
	{
		ft_putstr("No file found with the following name: ");
		big_struc->last_ret = 127;
		ft_putendl(command[i]);
		free_env(env);
		return (NULL);
	}
	tab_env = compact_env(env);
	exec_command_gen(right_path, argv, tab_env);
	return (right_path);
}

int		exec_default_env(t_env *env, char **command,
	t_hustru *big_struc, int flags)
{
	(void)env;
	printf("Je passe par ici\n");
	exec_file_env(big_struc->lkd_env, command, big_struc, flags);
	return (0);
}

int		launch_command_env(t_hustru *big_struc, int flags,
	char **command)
{
	t_env	*env;
	int		is_command;
	t_env	*lkd_env;

	lkd_env = big_struc->lkd_env;
	is_command = 1;
	env = parse_env(lkd_env, command, flags, &is_command);
	if (is_command == 1 && flags & PE_I)
		exec_file_env(env, command, big_struc, flags);
	else if (is_command == 1)
		exec_default_env(env, command, big_struc, flags);
	return (0);
}

int		print_env(t_hustru *big_struc, char **command)
{
	if (!command[1])
		return (print_basic_env(big_struc->lkd_env, 0, 0));
	else
		return (parsing_env(big_struc, command));
}
