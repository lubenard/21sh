/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_lkd_lst.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/16 15:56:10 by lubenard          #+#    #+#             */
/*   Updated: 2019/05/16 16:02:38 by lubenard         ###   ########.fr       */
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
	return (NULL);
}
