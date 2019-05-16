/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/15 14:53:06 by lubenard          #+#    #+#             */
/*   Updated: 2019/05/16 15:52:11 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

char	*g_username;
char	*g_curr_dir;

void	change_env(t_env *lkd_env)
{
	char buff[4096];
	char *str;
	int i;

	str = find_in_env(lkd_env, ft_strdup("SHLVL"));
	if (str == NULL)
	{
		ft_strcpy(buff, "setenv SHLVL=1");
		free(str);
		set_env(lkd_env, buff);
	}
	else
	{
		ft_strcpy(buff, "setenv SHLVL=");
		i = ft_atoi(str) + 1;
		free(str);
		set_env(lkd_env, ft_strcat(buff, str = ft_itoa(i)));
	}
}

void	free_after_exit(t_env *lkd_env)
{
	t_env *tmp;

	while (lkd_env)
	{
		tmp = lkd_env;
		lkd_env = lkd_env->next;
		free(tmp);
	}
}

char	*get_path_hist(void)
{
	char buff[4097];
	char *path;

	path = getcwd(buff, 4096);
	return (path);
}

int		main(int argc, char **argv, char **env)
{
	t_env	*lkd_env;
	t_hist	*lkd_hist;

	(void)argc;
	(void)argv;
	lkd_env = get_env(env);
	display_prompt("user", "mon_path");
	lkd_hist = new_maillon_hist();
	change_env(lkd_env);
	save_command(&lkd_hist, "test");
	set_env(lkd_env, "setenv PATH=🙄");
	print_env(lkd_env);
	return (0);
}
