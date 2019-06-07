/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/20 18:37:25 by lubenard          #+#    #+#             */
/*   Updated: 2019/06/07 10:46:33 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

t_env	*new_maillon_env(void)
{
	t_env		*new_element;

	if (!(new_element = (t_env *)malloc(sizeof(t_env))))
		return (NULL);
	ft_bzero(new_element->env_line, 2056);
	new_element->next = NULL;
	new_element->prev = NULL;
	return (new_element);
}

t_env	*null_env(t_env *lkd_env)
{
	ft_strcpy(lkd_env->env_line, "");
	return (lkd_env);
}

t_env	*get_env(char **env)
{
	t_env	*lkd_env;
	t_env	*tmp;
	int		i;
	t_env	*new_element;

	i = 0;
	lkd_env = new_maillon_env();
	if (env[0] == NULL)
		return (null_env(lkd_env));
	tmp = lkd_env;
	while (env[i])
	{
		ft_strcpy(lkd_env->env_line, env[i]);
		if (env[i + 1] != NULL)
		{
			new_element = new_maillon_env();
			lkd_env->next = new_element;
			lkd_env->next->prev = lkd_env;
			lkd_env = lkd_env->next;
		}
		++i;
	}
	return (tmp);
}
