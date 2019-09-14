/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_env2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/22 13:46:20 by lubenard          #+#    #+#             */
/*   Updated: 2019/09/14 16:09:35 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <env.h>

void	fill_env2(t_env *tmp, char **command, int i)
{
	char *first_env;
	char *first_env2;

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

t_env	*print_env_no_command(t_env *env, int flags, int *is_command)
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
	free_env(tmp);
	return (NULL);
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
