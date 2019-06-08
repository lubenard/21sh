/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_lkd_lst.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/16 15:56:10 by lubenard          #+#    #+#             */
/*   Updated: 2019/06/08 13:19:46 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../sh21.h"

char	*find_in_env(t_env *lkd_env, char *to_find)
{
	int		i;
	int		e;
	char	*occur;

	i = 0;
	e = 0;
	while (lkd_env)
	{
		occur = extract_first_env(lkd_env->env_line, 0);
		if (!ft_strcmp(occur, to_find))
		{
			while (lkd_env->env_line[i] && lkd_env->env_line[i] != '=')
				i++;
			i++;
			while (lkd_env->env_line[i + e])
				e++;
			free(to_find);
			free(occur);
			return (ft_strsub(lkd_env->env_line, i, e));
		}
		free(occur);
		lkd_env = lkd_env->next;
	}
	free(to_find);
	return (NULL);
}
