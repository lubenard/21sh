/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_env2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/22 13:46:20 by lubenard          #+#    #+#             */
/*   Updated: 2019/08/22 14:19:42 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <env.h>

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
