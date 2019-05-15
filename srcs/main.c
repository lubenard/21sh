/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/15 14:53:06 by lubenard          #+#    #+#             */
/*   Updated: 2019/05/15 17:12:11 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

void	change_env(t_env *lkd_env)
{
	char buff[4096];
	char *str;
	int i;

	str = find_in_env(lkd_env, ft_strdup("SHLVL"));
	if (ft_strcmp(str, ""))
	{
		ft_strcpy(buff, "setenv SHLVL=");
		i = ft_atoi(str) + 1;
		free(str);
		set_env(lkd_env, ft_strcat(buff, str = ft_itoa(i)));
	}
	free(str);
}

int		main(int argc, char **argv, char **env)
{
	t_env *lkd_env;

	lkd_env = get_env(env);
	change_env(lkd_env);
	(void)argc;
	(void)argv;
	return (0);
}
