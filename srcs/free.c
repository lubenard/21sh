/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/03 17:01:28 by lubenard          #+#    #+#             */
/*   Updated: 2019/09/11 22:40:23 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

int		free_after_exec(char *get_right_path, char **env)
{
	free(get_right_path);
	free(env);
	return (0);
}

void	free_env(t_env *env)
{
	(void)env;
	/*t_env	*tmp;
	int		i;

	i = 0;
	while (env)
	{
		tmp = env;
		env = env->next;
		free(tmp);
	}*/
}

char	*extract_command(char *command)
{
	int i;
	int e;

	i = 0;
	e = 0;
	while (ft_isalnum(command[i + e])
	|| command[i + e] == '.' || command[i + e] == '/')
		++i;
	return (ft_strlower(ft_strsub(command, e, i)));
}
