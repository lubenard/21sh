/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/15 16:15:46 by lubenard          #+#    #+#             */
/*   Updated: 2019/05/15 16:55:53 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../sh21.h"

char	*find_in_env(t_env *lkd_env, char *to_find)
{
	int lenght;
	int i;
	int e;

	i = 0;
	e = 0;
	lenght = ft_strlen(to_find);
	while (lkd_env)
	{
		if (ft_strncmp(lkd_env->env_line, to_find, lenght) == 0)
		{
			while (lkd_env->env_line[i] && lkd_env->env_line[i] != '=')
				i++;
			i++;
			while (lkd_env->env_line[i + e])
				e++;
			free(to_find);
			return (ft_strsub(lkd_env->env_line, i, e));
		}
		lkd_env = lkd_env->next;
	}
	free(to_find);
	return (ft_strdup(""));
}

void	print_env(t_env *lkd_env)
{
	while (lkd_env)
	{
		if (ft_strcmp(lkd_env->env_line, ""))
		{
			ft_putstr(lkd_env->env_line);
			ft_putchar('\n');
		}
		lkd_env = lkd_env->next;
	}
}
